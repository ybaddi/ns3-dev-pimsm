/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

//
// Simple example of OLSR routing over some point-to-point links
//
// Network topology
//
//   n0
//     \ 5 Mb/s, 2ms
//      \          1.5Mb/s, 10ms
//       n2 -------------------------n3---------n4
//      /
//     / 5 Mb/s, 2ms
//   n1
//
// - all links are point-to-point links with indicated one-way BW/delay
// - CBR/UDP flows from n0 to n4, and from n3 to n1
// - UDP packet size of 210 bytes, with per-packet interval 0.00375 sec.
//   (i.e., DataRate of 448,000 bps)
// - DropTail queues
// - Tracing of queues and packet receptions to file "simple-point-to-point-olsr.tr"

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/core-module.h"
#include "ns3/pim-sm-module.h"
#include "ns3/pim-sm-helper.h"
#include "ns3/packet.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SimplePIM-SMExample");

int 
main (int argc, char *argv[])
{
  bool verbose = true;
  LogComponentEnable("PIM-SM", LOG_LEVEL_ALL);
  NS_LOG_INFO ("PIM-SM example");
  CommandLine cmd;
  cmd.AddValue ("verbose", "Tell application to log if true", verbose);

  cmd.Parse (argc,argv);
  // Here, we will explicitly create four nodes.  In more sophisticated
  // topologies, we could configure a node factory.
  NS_LOG_INFO ("Create nodes.");
  NodeContainer c;
  c.Create (5);
  NodeContainer n02 = NodeContainer (c.Get (0), c.Get (2));
  NodeContainer n12 = NodeContainer (c.Get (1), c.Get (2));
  NodeContainer n32 = NodeContainer (c.Get (3), c.Get (2));
  NodeContainer n34 = NodeContainer (c.Get (3), c.Get (4));

  /* ... */
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));
  NetDeviceContainer nd02 = p2p.Install (n02);
  NetDeviceContainer nd12 = p2p.Install (n12);
  p2p.SetDeviceAttribute ("DataRate", StringValue ("1500kbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("10ms"));
  NetDeviceContainer nd32 = p2p.Install (n32);
  NetDeviceContainer nd34 = p2p.Install (n34);

  // Enable OLSR
  NS_LOG_INFO ("Enabling OLSR Routing.");
  PimsmHelper pimsm;

  Ipv4StaticRoutingHelper staticRouting;

  Ipv4ListRoutingHelper list;
  list.Add (staticRouting, 0);
  list.Add (pimsm, 10);


  p2p.EnablePcapAll ("pim-sm-example");



  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}


