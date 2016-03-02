/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "ns3/pim-sm-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"

#include "ns3/packet.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("PIM-SMExample");

int 
main (int argc, char *argv[])
{
  bool verbose = true;
  LogComponentEnable("PIM-SM", LOG_LEVEL_INFO);
  CommandLine cmd;
  cmd.AddValue ("verbose", "Tell application to log if true", verbose);

  cmd.Parse (argc,argv);

  /* ... */
  NS_LOG_INFO ("creating the nodes");


  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}


