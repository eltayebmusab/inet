//
// Copyright (C) 2020 OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include "inet/queueing/scheduler/WrrScheduler.h"

#include "inet/common/INETUtils.h"

namespace inet {
namespace queueing {

Define_Module(WrrScheduler);

WrrScheduler::~WrrScheduler()
{
    delete[] weights;
    delete[] buckets;
}

void WrrScheduler::initialize(int stage)
{
    PacketSchedulerBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        weights = new int[providers.size()];
        buckets = new int[providers.size()];

        auto weightsArray = check_and_cast<cValueArray *>(par("weights").objectValue())->asIntVector();
        if (weightsArray.size() < providers.size())
            throw cRuntimeError("Too few values given in the weights parameter.");
        if (weightsArray.size() > providers.size())
            throw cRuntimeError("Too many values given in the weights parameter.");
        for (size_t i = 0; i < providers.size(); ++i)
            buckets[i] = weights[i] = weightsArray[i];

        for (auto provider : providers)
            collections.push_back(dynamic_cast<IPacketCollection *>(provider));
    }
}

int WrrScheduler::getNumPackets() const
{
    int size = 0;
    for (auto collection : collections)
        size += collection->getNumPackets();
    return size;
}

b WrrScheduler::getTotalLength() const
{
    b totalLength(0);
    for (auto collection : collections)
        totalLength += collection->getTotalLength();
    return totalLength;
}

int WrrScheduler::schedulePacket()
{
    bool isEmpty = true;
    for (int i = 0; i < (int)providers.size(); ++i) {
        if (providers[i]->canPullSomePacket(inputGates[i]->getPathStartGate())) {
            isEmpty = false;
            if (buckets[i] > 0) {
                buckets[i]--;
                return i;
            }
        }
    }

    if (isEmpty)
        return -1;

    int result = -1;
    for (int i = 0; i < (int)providers.size(); ++i) {
        buckets[i] = weights[i];
        if (result == -1 && buckets[i] > 0 && providers[i]->canPullSomePacket(inputGates[i]->getPathStartGate())) {
            buckets[i]--;
            result = i;
        }
    }
    return result;
}

} // namespace queueing
} // namespace inet

