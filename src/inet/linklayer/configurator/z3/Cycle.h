#ifndef __INET_Z3_CYCLE_H
#define __INET_Z3_CYCLE_H

#include <z3++.h>

#include "inet/common/INETDefs.h"

namespace inet {

using namespace z3;

/**
 * [Class]: Cycle
 * [Usage]: Contains all properties of a TSN cycle.
 * After the specification of its properties through
 * user input, the toZ3 method can be used to convert
 * the values to z3 variables and query the unknown
 * values.
 *
 * There is no direct reference from a cycle to
 * its time slots. The user must use a priority from a flow
 * to reference the time window of a cycle. This happens
 * because of the generation of z3 variables.
 *
 * For example, if I want to know the duration of the time slot
 * reserved for the priority 3, it most likely will return a value
 * different from the actual time slot that a flow is making use.
 * This happens due to the way that z3 variables are generated. A flow
 * fragment can have a priority 3 on this cycle, but its variable
 * name will be "flowNfragmentMpriority". Even if z3 says that this
 * variable 3, the reference to the cycle duration will be called
 * "cycleXSlotflowNfragmentMpriorityDuration", which is clearly different
 * from "cycleXSlot3Duration".
 *
 * To make this work, every flow that has the same time window has the
 * same priority value. And this value is limited to a maximum value
 * (numOfSlots). So, to access the slot start and duration of a certain
 * priority, a flow fragment from that priority must be retrieved.
 *
 * This also deals with the problem of having unused priorities,
 * which can end up causing problems due to constraints of guard band
 * and such.
 *
 */
class INET_API Cycle {
    std::string portName = "";
	static int instanceCounter = 0;
    float upperBoundCycleTime;
    float lowerBoundCycleTime;
    float firstCycleStart;
    float maximumSlotDuration;

    float cycleDuration;
    float cycleStart;

    std::vector<std::vector<z3::expr>> slotStartZ3;
    std::vector<std::vector<z3::expr>> slotDurationZ3;

    std::vector<int> slotsUsed;
    std::vector<std::vector<float>> slotStart;
    std::vector<std::vector<float>> slotDuration;

    z3::expr cycleDurationZ3;
    z3::expr firstCycleStartZ3;
    z3::expr maximumSlotDurationZ3;
    int numOfPrts = 8;

    int numOfSlots = 1;



	/**
     * [Method]: Cycle
     * [Usage]: Overloaded method of this class. Will create
     * an object setting up the minimum and maximum cycle time,
     * the first cycle start and the maximum duration of a
     * priority slot. Other constructors either are deprecated
     * or set parameters that will be used in future works.
     *
     *
     * @param upperBoundCycleTime   Maximum size of the cycle
     * @param lowerBoundCycleTime   Minimum size of the cycle
     * @param maximumSlotDuration   Every priority slot should have up this time units
     */
    Cycle(float upperBoundCycleTime,
                 float lowerBoundCycleTime,
                 float maximumSlotDuration) {
        this->upperBoundCycleTime = upperBoundCycleTime;
        this->lowerBoundCycleTime = lowerBoundCycleTime;
        this->maximumSlotDuration = maximumSlotDuration;
        this->firstCycleStart = 0;
    }


    Cycle(float maximumSlotDuration) {
       this->maximumSlotDuration = maximumSlotDuration;
       this->firstCycleStart = 0;
    }


    /**
     * [Method]: Cycle
     * [Usage]: Overloaded method of this class. Will create
     * an object setting up the minimum and maximum cycle time,
     * the first cycle start and the maximum duration of a
     * priority slot.
     *
     *
     * @param upperBoundCycleTime   Maximum size of the cycle
     * @param lowerBoundCycleTime   Minimum size of the cycle
     * @param firstCycleStart       Where the first cycle should start
     * @param maximumSlotDuration   Every priority slot should have up this time units
     */
    Cycle(float upperBoundCycleTime,
                 float lowerBoundCycleTime,
                 float firstCycleStart,
                 float maximumSlotDuration) {
        this->upperBoundCycleTime = upperBoundCycleTime;
        this->lowerBoundCycleTime = lowerBoundCycleTime;
        this->firstCycleStart = firstCycleStart;
        this->maximumSlotDuration = maximumSlotDuration;
    }

    /**
     * [Method]: Cycle
     * [Usage]: Overloaded method of this class. Will create
     * an object setting up the minimum and maximum cycle time,
     * the first cycle start and the maximum duration of a
     * priority slot. These properties must be given as z3
     * variables.
     *
     *
     * @param upperBoundCycleTimeZ3   Maximum size of the cycle
     * @param lowerBoundCycleTimeZ3   Minimum size of the cycle
     * @param firstCycleStartZ3       Where the first cycle should start
     * @param maximumSlotDurationZ3   Every priority slot should have up this time units
     */
    Cycle(z3::expr upperBoundCycleTimeZ3,
                 z3::expr lowerBoundCycleTimeZ3,
                 z3::expr firstCycleStartZ3,
                 z3::expr maximumSlotDurationZ3) {
        // this->upperBoundCycleTimeZ3 = upperBoundCycleTimeZ3;
        // this->lowerBoundCycleTimeZ3 = lowerBoundCycleTimeZ3;
        this->firstCycleStartZ3 = firstCycleStartZ3;
        //this->guardBandSizeZ3 = guardBandSize;
        this->maximumSlotDurationZ3 = maximumSlotDurationZ3;
    }

    /**
     * [Method]: toZ3
     * [Usage]: After setting all the numeric input values of the class,
     * generates the z3 equivalent of these values and creates any extra
     * variable needed.
     *
     * @param ctx      context variable containing the z3 environment used
     */
    void toZ3(context ctx) {
        instanceCounter++;

        this->cycleDurationZ3 = ctx.real_const("cycle" + int.toString(instanceCounter) + "Duration");
        this->firstCycleStartZ3 = ctx.real_const("cycle" + int.toString(instanceCounter) + "Start");
        // this->firstCycleStartZ3 = ctx.real_val(std::to_string(0));
        // this->firstCycleStartZ3 = ctx.real_val(std::to_string(firstCycleStart));
        this->maximumSlotDurationZ3 = ctx.real_val(std::to_string(maximumSlotDuration));

        this->slotStartZ3.clear();
        this->slotDurationZ3.clear();

        for(int i = 0; i < this->numOfPrts; i++) {
        	this->slotStartZ3.add(std::vector<z3::expr>());
        	this->slotDurationZ3.add(std::vector<z3::expr>());
        	for(int j = 0; j < this->numOfSlots; j++) {
        		this->slotStartZ3.get(i).add(ctx.real_const("cycleOfPort" + this->portName + "prt" + (i+1) + "slot" + (j+1)));
        	}
        }

    }


    /**
     * [Method]: cycleStartZ3
     * [Usage]: Returns the time of the start of a cycle
     * specified by its index. The index is given as a z3
     * variable
     *
     * @param ctx       context containing the z3 environment
     * @param index     Index of the desired cycle
     * @return          Z3 variable containing the cycle start time
     */
    z3::expr cycleStartZ3(context ctx, z3::expr index){
        return (z3::expr) ctx.mkITE(
                ctx.mkGe(index, ctx.mkInt(1)),
                ctx.mkAdd(
                        firstCycleStartZ3,
                        ctx.mkMul(cycleDurationZ3, index)
                        ),
                firstCycleStartZ3);

     }

    /**
     * [Method]: cycleStartZ3
     * [Usage]: Returns the time of the start of a cycle
     * specified by its index. The index is given as integer
     *
     * @param ctx       context containing the z3 environment
     * @param index     Index of the desired cycle
     * @return          Z3 variable containing the cycle start time
     */
    z3::expr cycleStartZ3(context ctx, int auxIndex){
        z3::expr index = ctx.mkInt(auxIndex);

        return (z3::expr) ctx.mkITE(
                ctx.mkGe(index, ctx.mkInt(1)),
                ctx.mkAdd(
                        firstCycleStartZ3,
                        ctx.mkMul(cycleDurationZ3, index)
                        ),
                firstCycleStartZ3);

     }


    /**
     * [Method]: addSlotUsed
     * [Usage]: After generating the schedule, the z3 values are
     * converted to floats and integers. The used slots are now
     * placed on a arrayList, and so are the slot start and duration.
     *
     * @param prt           Priority of the slot to be added
     * @param sStart        Slot start of the slot to be added
     * @param sDuration     Slot duration of the slot to be added
     */
    void addSlotUsed(int prt, std::vector<float> sStart, std::vector<float> sDuration) {

        if(!this->slotsUsed.contains(prt)) {
            this->slotsUsed.add(prt);
            this->slotStart.add(sStart);
            this->slotDuration.add(sDuration);
        }

    }


    /**
     * [Method]: loadZ3
     * [Usage]: From the loaded primitive values of the class
     * obtained in the deserialization process, initialize the
     * z3 variables.
     *
     * @param ctx		context object of z3
     * @param solver	solver object to add constraints
     */
    void loadZ3(context ctx, solver solver) {
    	// maximumSlotDurationZ3 already started on toZ3;

    	solver.add(
			ctx.mkEq(
				this->cycleDurationZ3,
				ctx.real_val(std::to_string(this->cycleDuration))
			)
		);

    	solver.add(
			ctx.mkEq(
				this->firstCycleStartZ3,
				ctx.real_val(std::to_string(this->firstCycleStart))
			)
		);


    	for(int prt : this->getSlotsUsed()) {

    		// Where are the slot duration per priority instantiated? Must do it before loading

    		for(int slotIndex = 0; slotIndex < this->numOfSlots; slotIndex++) {
    			solver.add(
					ctx.mkEq(
						this->slotStartZ3.get(prt).get(slotIndex),
						ctx.real_val(std::to_string(this->slotStart.get(this->slotsUsed.indexOf(prt)).get(slotIndex)))
					)
				);
    		}

    		/*
    		for(int slotIndex = 0; slotIndex < this->numOfSlots; slotIndex++) {
    			solver.add(
					ctx.mkEq(
						this->slotDurationZ3.get(prt).get(slotIndex),
						ctx.real_val(std::to_string(this->slotDuration.get(prt).get(slotIndex)))
					)
				);
    		}
    		*/
    	}



    }

    /*
     *  GETTERS AND SETTERS
     */


    float getUpperBoundCycleTime() {
        return upperBoundCycleTime;
    }

    void setUpperBoundCycleTime(float upperBoundCycleTime) {
        this->upperBoundCycleTime = upperBoundCycleTime;
    }

    float getLowerBoundCycleTime() {
        return lowerBoundCycleTime;
    }

    void setLowerBoundCycleTime(float lowerBoundCycleTime) {
        this->lowerBoundCycleTime = lowerBoundCycleTime;
    }

    float getCycleDuration() {
        return cycleDuration;
    }

    float getCycleStart() {
        return cycleStart;
    }


    void setCycleStart(float cycleStart) {
        this->cycleStart = cycleStart;
    }

    void setCycleDuration(float cycleDuration) {
        this->cycleDuration = cycleDuration;
    }

    float getFirstCycleStart() {
        return firstCycleStart;
    }

    void setFirstCycleStart(float firstCycleStart) {
        this->firstCycleStart = firstCycleStart;
    }

    float getMaximumSlotDuration() {
        return maximumSlotDuration;
    }

    void setMaximumSlotDuration(float maximumSlotDuration) {
        this->maximumSlotDuration = maximumSlotDuration;
    }


    z3::expr slotStartZ3(context ctx, z3::expr prt, z3::expr index) {
        return ctx.real_const("priority" + prt.toString() + "slot" + index.toString() + "Start");
    }

    z3::expr slotStartZ3(context ctx, int auxPrt, int auxIndex) {
        z3::expr index = ctx.mkInt(auxIndex);
        z3::expr prt = ctx.mkInt(auxPrt);
        return ctx.real_const("priority" + prt.toString() + "slot" + index.toString() + "Start");
    }


    z3::expr slotDurationZ3(context ctx, z3::expr prt, z3::expr index) {
        return ctx.real_const("priority" + prt.toString() + "slot" + index.toString() + "Duration");
    }

    z3::expr slotDurationZ3(context ctx, int auxPrt, int auxIndex) {
        z3::expr index = ctx.mkInt(auxIndex);
        z3::expr prt = ctx.mkInt(auxPrt);
        return ctx.real_const("priority" + prt.toString() + "slot" + index.toString() + "Duration");
    }

    z3::expr getCycleDurationZ3() {
        return cycleDurationZ3;
    }

    void setCycleDurationZ3(z3::expr cycleDuration) {
        this->cycleDurationZ3 = cycleDuration;
    }

    z3::expr getFirstCycleStartZ3() {
        return firstCycleStartZ3;
    }

    void setFirstCycleStartZ3(z3::expr firstCycleStart) {
        this->firstCycleStartZ3 = firstCycleStart;
    }

    int getNumOfPrts() {
        return this->numOfPrts;
    }

    void setNumOfPrts(int numOfPrts) {
        this->numOfPrts = numOfPrts;
    }

    int getNumOfSlots() {
		return numOfSlots;
	}

     void setNumOfSlots(int numOfSlots) {
		this->numOfSlots = numOfSlots;
	}

    z3::expr getMaximumSlotDurationZ3() {
        return maximumSlotDurationZ3;
    }

    void setMaximumSlotDurationZ3(z3::expr maximumSlotDuration) {
        this->maximumSlotDurationZ3 = maximumSlotDuration;
    }

    std::vector<int> getSlotsUsed (){
        return this->slotsUsed;
    }

    std::vector<std::vector<float>> getSlotDuration() {
        return slotDuration;
    }

    float getSlotStart(int prt, int index) {
        return this->slotStart.get(this->slotsUsed.indexOf(prt)).get(index);
    }

    float getSlotDuration(int prt, int index) {
        return this->slotDuration.get(this->slotsUsed.indexOf(prt)).get(index);
    }

    std::string getPortName() {
		return portName;
	}


     void setPortName(std::string portName) {
		this->portName = portName;
	}

     z3::expr getSlotStartZ3(int prt, int slotNum) {
		return this->slotStartZ3.get(prt).get(slotNum);
	}

	/*
     z3::expr getSlotDurationZ3(int prt, int slotNum) {
		return this->slotDurationZ3.get(prt).get(slotNum);
	}
	*/
};

}

#endif
