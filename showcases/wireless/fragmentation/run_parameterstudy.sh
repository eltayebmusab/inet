#!/bin/bash

opp_runall inet -u Cmdenv -f parameterstudy.ini -c PacketSizeDCFnofrag
opp_runall inet -u Cmdenv -f parameterstudy.ini -c PacketSizeDCFfrag
opp_runall inet -u Cmdenv -f parameterstudy.ini -c PacketSizeHCFfrag
opp_runall inet -u Cmdenv -f parameterstudy.ini -c PacketSizeHCFfragblockack
opp_runall inet -u Cmdenv -f parameterstudy.ini -c TxPowerDCFnofrag
opp_runall inet -u Cmdenv -f parameterstudy.ini -c TxPowerDCFfrag
opp_runall inet -u Cmdenv -f parameterstudy.ini -c TxPowerHCFfrag
opp_runall inet -u Cmdenv -f parameterstudy.ini -c TxPowerHCFfragblockack
opp_runall inet -u Cmdenv -f parameterstudy.ini -c ThresholdDCFfrag
opp_runall inet -u Cmdenv -f parameterstudy.ini -c ThresholdHCFfrag
opp_runall inet -u Cmdenv -f parameterstudy.ini -c ThresholdHCFfragblockack
opp_runall inet -u Cmdenv -f parameterstudy.ini -c OnlyPacketSizeDCFnofrag
opp_runall inet -u Cmdenv -f parameterstudy.ini -c OnlyPacketSizeDCFfrag
opp_runall inet -u Cmdenv -f parameterstudy.ini -c OnlyPacketSizeHCFfrag
opp_runall inet -u Cmdenv -f parameterstudy.ini -c OnlyPacketSizeHCFfragblockack
