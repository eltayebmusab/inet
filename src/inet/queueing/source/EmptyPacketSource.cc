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

#include "inet/common/ModuleAccess.h"
#include "inet/queueing/source/EmptyPacketSource.h"

namespace inet {
namespace queueing {

Define_Module(EmptyPacketSource);

void EmptyPacketSource::initialize(int stage)
{
    PacketProcessorBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        outputGate = gate("out");
        consumer = findConnectedModule<IPassivePacketSink>(outputGate);
    }
    else if (stage == INITSTAGE_QUEUEING)
        checkPacketOperationSupport(outputGate);
}

void EmptyPacketSource::handleCanPushPacketChanged(cGate *gate)
{
    Enter_Method("handleCanPushPacketChanged");
}

void EmptyPacketSource::handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful)
{
    Enter_Method("handlePushPacketProcessed");
}

} // namespace queueing
} // namespace inet

