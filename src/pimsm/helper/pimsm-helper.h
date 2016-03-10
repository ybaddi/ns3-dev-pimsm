/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef PIM_SM_HELPER_H
#define PIM_SM_HELPER_H

#include "ns3/object-factory.h"
#include "ns3/node.h"
#include "ns3/node-container.h"
#include "ns3/ipv4-static-routing-helper.h"
#include <map>
#include <set>

namespace ns3 {

/**
 * \brief Helper class that adds pimsm routing to nodes.
 *
 * This class is expected to be used in conjunction with
 * ns3::InternetStackHelper::SetRoutingHelper
 */


    class PimsmHelper : public Ipv4RoutingHelper
    {
    public:
        /**
   * Create an OlsrHelper that makes life easier for people who want to install
   * pimsm routing to nodes.
   */
        PimsmHelper ();

        /**
         * destructor
         */

        ~PimsmHelper ();


        /**
       * \brief Construct an OlsrHelper from another previously initialized instance
       * (Copy Constructor).
       */
        //PimsmHelper (const PimsmHelper &);

        /**
         * \returns pointer to clone of this OlsrHelper
         *
         * This method is mainly for internal use by the other helpers;
         * clients are expected to free the dynamic memory allocated by this method
         */
        //PimsmHelper* Copy (void) const;

        /**
    * \param node the node for which an exception is to be defined
    * \param interface an interface of node on which OLSR is not to be installed
    *
    * This method allows the user to specify an interface on which OLSR is not to be installed on
    */
        //void ExcludeInterface (Ptr<Node> node, uint32_t interface);

        /**
   * \param node the node on which the routing protocol will run
   * \returns a newly-created routing protocol
   *
   * This method will be called by ns3::InternetStackHelper::Install
   */
        //virtual Ptr<Ipv4RoutingProtocol> Create (Ptr<Node> node) const;

        /**
         * \param name the name of the attribute to set
         * \param value the value of the attribute to set.
         *
         * This method controls the attributes of ns3::olsr::RoutingProtocol
         */
        //void Set (std::string name, const AttributeValue &value);

        /**
         * Assign a fixed random variable stream number to the random variables
         * used by this model.  Return the number of streams (possibly zero) that
         * have been assigned.  The Install() method of the InternetStackHelper
         * should have previously been called by the user.
         *
         * \param stream first stream index to use
         * \param c NodeContainer of the set of nodes for which the OlsrRoutingProtocol
         *          should be modified to use a fixed stream
         * \return the number of stream indices assigned by this helper
         */
        //int64_t AssignStreams (NodeContainer c, int64_t stream);

    private:
        PimsmHelper &operator = (const PimsmHelper &);
        //ObjectFactory m_agentFactory; //!< Object factory

        //std::map< Ptr<Node>, std::set<uint32_t> > m_interfaceExclusions; //!< container of interfaces excluded from OLSR operations

    };


}

#endif /* PIM_SM_HELPER_H */

