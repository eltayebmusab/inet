/*******************************************************************
*
*    This library is free software, you can redistribute it
*    and/or modify
*    it under  the terms of the GNU Lesser General Public License
*    as published by the Free Software Foundation;
*    either version 2 of the License, or any later version.
*    The library is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*    See the GNU Lesser General Public License for more details.
*
*
*********************************************************************/

#ifndef __RSVPPATHMSG_H__
#define __RSVPPATHMSG_H__

#include "RSVPPathMsg_m.h"


/**
 * RSVP PATH message
 */
class RSVPPathMsg : public RSVPPathMsg_Base
{
  public:
    RSVPPathMsg(const char *name=NULL, int kind=PATH_MESSAGE) : RSVPPathMsg_Base(name,kind) {}
    RSVPPathMsg(const RSVPPathMsg& other) : RSVPPathMsg_Base(other.name()) {operator=(other);}
    RSVPPathMsg& operator=(const RSVPPathMsg& other) {RSVPPathMsg_Base::operator=(other); return *this;}
    virtual cObject *dup() {return new RSVPPathMsg(*this);}

    inline int getSrcAddress() {return getSender_descriptor().Sender_Template_Object.SrcAddress;}
    inline int getSrcPort() {return getSender_descriptor().Sender_Template_Object.SrcPort;}
    inline int getLspId() {return getSender_descriptor().Sender_Template_Object.Lsp_Id;}
    inline int getNHOP() {return getRsvp_hop().Next_Hop_Address;}
    inline int getLIH() {return getRsvp_hop().Logical_Interface_Handle;}
    inline double getDelay() {return getSender_descriptor().Sender_Tspec_Object.link_delay;}
    inline double getBW() {return getSender_descriptor().Sender_Tspec_Object.req_bandwidth;}
    inline bool hasERO() {return getHasERO();}
    inline SenderTemplateObj_t* getSenderTemplate() {return &getSender_descriptor().Sender_Template_Object;}
    inline void setSenderTemplate(const SenderTemplateObj_t& s) {getSender_descriptor().Sender_Template_Object = s;}
    inline SenderTspecObj_t* getSenderTspec() {return &getSender_descriptor().Sender_Tspec_Object;}
    inline void setSenderTspec(const SenderTspecObj_t& s) {getSender_descriptor().Sender_Tspec_Object = s;}
    inline EroObj_t* getEROArrayPtr() {return ERO_var;} //FIXME
    inline void setEROArray(EroObj_t* ero) {for (int i=0; i<MAX_ROUTE; i++) setERO(i,ero[i]);}
    bool equalST(SenderTemplateObj_t* s);
    bool equalSD(SenderDescriptor_t* s);

    void print();
};

inline bool RSVPPathMsg::equalST(SenderTemplateObj_t * s)
{
    return getSender_descriptor().Sender_Template_Object.SrcAddress == s->SrcAddress &&
           getSender_descriptor().Sender_Template_Object.SrcPort == s->SrcPort &&
           getSender_descriptor().Sender_Template_Object.Lsp_Id == s->Lsp_Id;
}

inline bool RSVPPathMsg::equalSD(SenderDescriptor_t * s)
{
    return getSender_descriptor().Sender_Template_Object.SrcAddress == s->Sender_Template_Object.SrcAddress &&
           getSender_descriptor().Sender_Template_Object.SrcPort == s->Sender_Template_Object.SrcPort &&
           getSender_descriptor().Sender_Template_Object.Lsp_Id == s->Sender_Template_Object.Lsp_Id &&
           getSender_descriptor().Sender_Tspec_Object.link_delay == s->Sender_Tspec_Object.link_delay &&
           getSender_descriptor().Sender_Tspec_Object.req_bandwidth == s->Sender_Tspec_Object.req_bandwidth;
}

inline void RSVPPathMsg::print()
{
    ev << "DestAddr = " << IPAddress(getDestAddress()) << "\n" <<
        "ProtId   = " << getProtId() << "\n" <<
        "DestPort = " << getDestPort() << "\n" <<
        "SrcAddr  = " << IPAddress(getSrcAddress()) << "\n" <<
        "SrcPort  = " << getSrcPort() << "\n" <<
        "Lsp_Id = " << getLspId() << "\n" <<
        "Next Hop = " << IPAddress(getNHOP()) << "\n" <<
        "LIH      = " << IPAddress(getLIH()) << "\n" <<
        "Delay    = " << getDelay() << "\n" << "Bandwidth= " << getBW() << "\n";

}

//---

/**
 * PATH TEAR message
 */
class RSVPPathTear : public RSVPPathTear_Base
{
  public:
    RSVPPathTear(const char *name=NULL, int kind=PTEAR_MESSAGE) : RSVPPathTear_Base(name,kind) {}
    RSVPPathTear(const RSVPPathTear& other) : RSVPPathTear_Base(other.name()) {operator=(other);}
    RSVPPathTear& operator=(const RSVPPathTear& other) {RSVPPathTear_Base::operator=(other); return *this;}
    virtual cObject *dup() {return new RSVPPathTear(*this);}

    inline int getNHOP() {return getRsvp_hop().Next_Hop_Address;}
    inline int getLIH() {return getRsvp_hop().Logical_Interface_Handle;}
    inline int getSrcAddress() {return getSenderTemplate().SrcAddress;}
    inline int getSrcPort() {return getSenderTemplate().SrcPort;}

    //inline SenderTemplateObj_t* getSenderTemplate() {return &senderTemplate;}
    //void setSenderTemplate(SenderTemplateObj_t* s);
    bool equalST(SenderTemplateObj_t* s);
    //void setHop(RsvpHopObj_t* h);
    void print();
};

inline bool RSVPPathTear::equalST(SenderTemplateObj_t * s)
{
    if (getSenderTemplate().SrcAddress == s->SrcAddress && getSenderTemplate().SrcPort == s->SrcPort)
        return true;
    return false;
}

inline void RSVPPathTear::print()
{
    ev << "DestAddr = " << IPAddress(getDestAddress()) << "\n" <<
        "ProtId   = " << getProtId() << "\n" <<
        "DestPort = " << getDestPort() << "\n" <<
        "SrcAddr  = " << IPAddress(getSrcAddress()) << "\n" <<
        "SrcPort  = " << getSrcPort() << "\n" <<
        "Next Hop = " << IPAddress(getNHOP()) << "\n" <<
        "LIH      = " << IPAddress(getLIH()) << "\n";
}

//---

/**
 * PATH ERROR packet
 */
class RSVPPathError : public RSVPPathError_Base
{
  public:
    RSVPPathError(const char *name=NULL, int kind=PERROR_MESSAGE) : RSVPPathError_Base(name,kind) {}
    RSVPPathError(const RSVPPathError& other) : RSVPPathError_Base(other.name()) {operator=(other);}
    RSVPPathError& operator=(const RSVPPathError& other) {RSVPPathError_Base::operator=(other); return *this;}
    virtual cObject *dup() {return new RSVPPathError(*this);}

    inline int getSrcAddress() {return getSender_descriptor().Sender_Template_Object.SrcAddress;}
    inline int getSrcPort() {return getSender_descriptor().Sender_Template_Object.SrcPort;}
    inline int getLspId() {return getSender_descriptor().Sender_Template_Object.Lsp_Id;}
    inline double getDelay() {return getSender_descriptor().Sender_Tspec_Object.link_delay;}
    inline double getBW() {return getSender_descriptor().Sender_Tspec_Object.req_bandwidth;}

    inline SenderTemplateObj_t& getSenderTemplate() {return getSender_descriptor().Sender_Template_Object;}
    inline void setSenderTemplate(const SenderTemplateObj_t& s) {getSender_descriptor().Sender_Template_Object = s;}
    inline SenderTspecObj_t& getSenderTspec() {return getSender_descriptor().Sender_Tspec_Object;}
    inline void setSenderTspec(const SenderTspecObj_t& s) {getSender_descriptor().Sender_Tspec_Object = s;}

    bool equalST(SenderTemplateObj_t* s);
    bool equalSD(SenderDescriptor_t* s);

};

inline bool RSVPPathError::equalST(SenderTemplateObj_t * s)
{
    if (getSender_descriptor().Sender_Template_Object.SrcAddress ==
        s->SrcAddress && getSender_descriptor().Sender_Template_Object.SrcPort == s->SrcPort)
        return true;
    return false;

}

inline bool RSVPPathError::equalSD(SenderDescriptor_t * s)
{
    if (getSender_descriptor().Sender_Template_Object.SrcAddress ==
        s->Sender_Template_Object.SrcAddress &&
        getSender_descriptor().Sender_Template_Object.SrcPort ==
        s->Sender_Template_Object.SrcPort &&
        getSender_descriptor().Sender_Tspec_Object.link_delay ==
        s->Sender_Tspec_Object.link_delay &&
        getSender_descriptor().Sender_Tspec_Object.req_bandwidth == s->Sender_Tspec_Object.req_bandwidth)
        return true;
    return false;
}

#endif



