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

#include "inet/queueing/base/PacketLabelerBase.h"

#include "inet/common/ModuleAccess.h"
#include "inet/queueing/common/LabelsTag_m.h"

namespace inet {
namespace queueing {

void PacketLabelerBase::initialize(int stage)
{
    PacketMarkerBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        labels = check_and_cast<cValueArray *>(par("labels").objectValue())->asStringVector();
    }
}

} // namespace queueing
} // namespace inet

