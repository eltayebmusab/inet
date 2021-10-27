Credit-Based Shaper
===================

Goals
-----

In this example we demonstrate how to use a credit-based shaping.

| INET version: ``4.4``
| Source files location: `inet/showcases/tsn/trafficshaping/creditbasedshaper <https://github.com/inet-framework/tree/master/showcases/tsn/trafficshaping/creditbasedshaper>`__

The Model
---------

In this configuration there are two independent data streams between two network
nodes that both pass through a switch where credit-based traffic shaping takes place.

Here is the network:

.. image:: media/Network.png
   :align: center
   :width: 100%

Here is the configuration:

.. literalinclude:: ../omnetpp.ini
   :language: ini

Results
-------

Here are the results:

.. figure:: media/SourceApplicationTraffic.png
   :align: center

.. figure:: media/SwitchInboundTraffic.png
   :align: center

.. figure:: media/SwitchOutboundTraffic.png
   :align: center

.. figure:: media/SwitchQueueLengths.png
   :align: center

.. figure:: media/TrafficClass0.png
   :align: center

.. figure:: media/TrafficClass1.png
   :align: center

.. figure:: media/DestinationApplicationTraffic.png
   :align: center

Sources: :download:`omnetpp.ini <../omnetpp.ini>`, :download:`CreditBasedShaperShowcase.ned <../CreditBasedShaperShowcase.ned>`

Discussion
----------

Use `this <https://github.com/inet-framework/inet/discussions/TODO>`__ page in the GitHub issue tracker for commenting on this showcase.

