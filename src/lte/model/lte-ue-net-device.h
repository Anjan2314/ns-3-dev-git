/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2010 TELEMATICS LAB, DEE - Politecnico di Bari
 *
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
 * Author: Giuseppe Piro  <g.piro@poliba.it>
 *         Nicola Baldo <nbaldo@cttc.es>
 * Modified by:
 *          Danilo Abrignani <danilo.abrignani@unibo.it> (Carrier Aggregation - GSoC 2015)
 *          Biljana Bojovic <biljana.bojovic@cttc.es> (Carrier Aggregation)
 */

#ifndef LTE_UE_NET_DEVICE_H
#define LTE_UE_NET_DEVICE_H

#include "ns3/lte-net-device.h"
#include "ns3/event-id.h"
#include "ns3/mac48-address.h"
#include "ns3/traced-callback.h"
#include "ns3/nstime.h"
#include "ns3/lte-phy.h"
#include "ns3/eps-bearer.h"
#include "ns3/component-carrier-ue.h"
#include <vector>
#include <map>

namespace ns3 {

class Packet;
class PacketBurst;
class Node;
class LtePhy;
class LteUePhy;
class LteEnbNetDevice;
class LteUeMac;
class LteUeRrc;
class EpcUeNas;
class EpcTft;
class LteUeComponentCarrierManager;

/**
 * \ingroup lte
 * The LteUeNetDevice class implements the UE net device
 */
class LteUeNetDevice : public LteNetDevice
{

public:
  static TypeId GetTypeId (void);

  LteUeNetDevice (void);
  virtual ~LteUeNetDevice (void);
  virtual void DoDispose ();


  // inherited from NetDevice
  virtual bool Send (Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber);


  Ptr<LteUeMac> GetMac (void) const;

  Ptr<LteUeRrc> GetRrc () const;

  Ptr<LteUePhy> GetPhy (void) const;

  Ptr<EpcUeNas> GetNas (void) const;
  
  Ptr<LteUeComponentCarrierManager> GetComponentCarrierManager (void) const;

  uint64_t GetImsi () const;

  /**
   * \return the downlink carrier frequency (EARFCN)
   *
   * Note that real-life handset typically supports more than one EARFCN, but
   * the sake of simplicity we assume only one EARFCN is supported.
   */
  uint32_t GetDlEarfcn () const;

  /**
   * \param earfcn the downlink carrier frequency (EARFCN)
   *
   * Note that real-life handset typically supports more than one EARFCN, but
   * the sake of simplicity we assume only one EARFCN is supported.
   */
  void SetDlEarfcn (uint32_t earfcn);

  /**
   * \brief Returns the CSG ID the UE is currently a member of.
   * \return the Closed Subscriber Group identity
   */
  uint32_t GetCsgId () const;

  /**
   * \brief Enlist the UE device as a member of a particular CSG.
   * \param csgId the intended Closed Subscriber Group identity
   *
   * UE is associated with a single CSG identity, and thus becoming a member of
   * this particular CSG. As a result, the UE may gain access to cells which
   * belong to this CSG. This does not revoke the UE's access to non-CSG cells.
   *
   * \note This restriction only applies to initial cell selection and
   *       EPC-enabled simulation.
   */
  void SetCsgId (uint32_t csgId);

  /**
   * \brief Set the targer eNB where the UE is registered
   * \param enb
   */
  void SetTargetEnb (Ptr<LteEnbNetDevice> enb);

  /**
   * \brief Get the targer eNB where the UE is registered
   * \return the pointer to the enb
   */
  Ptr<LteEnbNetDevice> GetTargetEnb (void);

  /**
   * \brief Set the ComponentCarrier Map for the UE
   * \param ccm the map of ComponentCarrierUe
   */
  void SetCcMap (std::map< uint8_t, Ptr<ComponentCarrierUe> > ccm);

  std::map< uint8_t, Ptr<ComponentCarrierUe> >  GetCcMap (void);



protected:
  // inherited from Object
  virtual void DoInitialize (void);


private:
  bool m_isConstructed;

  /**
   * \brief Propagate attributes and configuration to sub-modules.
   *
   * Several attributes (e.g., the IMSI) are exported as the attributes of the
   * LteUeNetDevice from a user perspective, but are actually used also in other
   * sub-modules (the RRC, the PHY, etc.). This method takes care of updating
   * the configuration of all these sub-modules so that their copy of attribute
   * values are in sync with the one in the LteUeNetDevice.
   */
  void UpdateConfig ();

  Ptr<LteEnbNetDevice> m_targetEnb;

  Ptr<LteUeMac> m_mac;
  Ptr<LteUePhy> m_phy;
  Ptr<LteUeRrc> m_rrc;
  Ptr<EpcUeNas> m_nas;
  Ptr<LteUeComponentCarrierManager> m_componentCarrierManager;

  uint64_t m_imsi;

  uint32_t m_dlEarfcn; /**< downlink carrier frequency */

  uint32_t m_csgId;

  std::map < uint8_t, Ptr<ComponentCarrierUe> > m_ccMap;

}; // end of class LteUeNetDevice

} // namespace ns3

#endif /* LTE_UE_NET_DEVICE_H */
