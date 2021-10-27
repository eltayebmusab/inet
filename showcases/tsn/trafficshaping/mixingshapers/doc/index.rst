Mixing Different Shapers
========================

Goals
-----

TODO

| INET version: ``4.4``
| Source files location: `inet/showcases/tsn/trafficshaping/mixingshapers <https://github.com/inet-framework/tree/master/showcases/tsn/trafficshaping/mixingshapers>`__

The Model
---------

Here is the network:

.. .. image:: media/Network.png
   :align: center
   :width: 100%

Here is the configuration:

.. literalinclude:: ../omnetpp.ini
   :align: center
   :language: ini

Results
-------

The first diagram shows the data rate (~48 Mbps) of the outgoing traffic of the
source applications.

.. figure:: media/SourceApplicationTraffic.png
   :align: center

The next diagram shows the data rate of the incoming traffic of the traffic
shapers of the outgoing network interface in the switch.

.. figure:: media/SwitchInboundTraffic.png
   :align: center

The next diagram shows the already shaped outgoing traffic of the outgoing
network interface in the switch.

.. figure:: media/SwitchOutboundTraffic.png
   :align: center

The next diagram shows the queue lengths of the traffic shapers in the outgoing
network interface of the switch. The queue lengths increase over time because
the datarate of the incoming traffic of the shapers is greater than the datarate
of the outgoing traffic.

.. figure:: media/SwitchQueueLengths.png
   :align: center

The next diagram shows the relationships for the high priority traffic class
between the number of credits, the gate state of the credit based transmission
selection algorithm and the transmitting state of the corresponding network
interface.

.. figure:: media/TrafficClass0.png
   :align: center

The next diagram shows the relationships for the best effort traffic class
between the gate state of the asynchronous transmission selection algorithm
and the transmitting state of the corresponding network interface.

.. figure:: media/TrafficClass1.png
   :align: center

The last diagram shows the data rate of the incoming traffic of the sink applications.

.. figure:: media/DestinationApplicationTraffic.png
   :align: center

Sources: :download:`omnetpp.ini <../omnetpp.ini>`, :download:`MixingShapersShowcase.ned <../MixingShapersShowcase.ned>`

Discussion
----------

Use `this <https://github.com/inet-framework/inet/discussions/TODO>`__ page in the GitHub issue tracker for commenting on this showcase.

