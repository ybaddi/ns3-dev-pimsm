//
// Created by baddi on 10/03/16.
//

#include "pim-multicast-forwarding-cache.h"
#include "ns3/core-module.h"
#include "ns3/log.h"

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE ("pim-mfc");

    namespace pimsm {

        PimMFC::PimMFC() {

        }

        void
        PimMFC::set_rp_addr(const Ipv4Address v) {
            NS_LOG_FUNCTION(this);

        }

    }

}