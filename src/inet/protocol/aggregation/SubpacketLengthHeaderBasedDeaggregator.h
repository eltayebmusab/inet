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

#ifndef __INET_SUBPACKETLENGTHHEADERBASEDDEAGGREGATOR_H
#define __INET_SUBPACKETLENGTHHEADERBASEDDEAGGREGATOR_H

#include "inet/protocol/aggregation/base/DeaggregatorBase.h"

namespace inet {

using namespace inet::queueing;

class INET_API SubpacketLengthHeaderBasedDeaggregator : public DeaggregatorBase
{
  protected:
    virtual void initialize(int stage) override;
    virtual std::vector<Packet *> deaggregatePacket(Packet *packet) override;
};

} // namespace inet

#endif

