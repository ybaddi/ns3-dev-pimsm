//
// Created by baddi on 10/03/16.
//

#include "ns3/ipv4-routing-protocol.h"

#ifndef NS3_MULTICAST_PIM_MULTICAST_FORWARDING_CACHE_H
#define NS3_MULTICAST_PIM_MULTICAST_FORWARDING_CACHE_H
namespace  ns3{
    namespace pimsm{

        class PimMFC : public Ipv4MulticastRoute{
        public:
            PimMFC ();

            void set_rp_addr(const Ipv4Address v);

        private:
        };
    }
}
#endif //NS3_MULTICAST_PIM_MULTICAST_FORWARDING_CACHE_H
