//
// Generated file, do not edit! Created by opp_msgc 4.2 from linklayer/can/CanFrame.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "CanFrame_m.h"

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("CanTrafficType");
    if (!e) enums.getInstance()->add(e = new cEnum("CanTrafficType"));
    e->insert(CAN_MESSAGE, "CAN_MESSAGE");
    e->insert(CAN_SEND_REQUEST, "CAN_SEND_REQUEST");
    e->insert(CAN_SEND_PERMIT, "CAN_SEND_PERMIT");
    e->insert(CAN_ARBITRATION_FINISH, "CAN_ARBITRATION_FINISH");
    e->insert(CAN_MESSAGES, "CAN_MESSAGES");
);

Register_Class(CanTraffic);

CanTraffic::CanTraffic(const char *name, int kind) : cPacket(name,kind)
{
    this->type_var = 0;
}

CanTraffic::CanTraffic(const CanTraffic& other) : cPacket(other)
{
    copy(other);
}

CanTraffic::~CanTraffic()
{
}

CanTraffic& CanTraffic::operator=(const CanTraffic& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void CanTraffic::copy(const CanTraffic& other)
{
    this->type_var = other.type_var;
}

void CanTraffic::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->type_var);
}

void CanTraffic::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->type_var);
}

short CanTraffic::getType() const
{
    return type_var;
}

void CanTraffic::setType(short type)
{
    this->type_var = type;
}

class CanTrafficDescriptor : public cClassDescriptor
{
  public:
    CanTrafficDescriptor();
    virtual ~CanTrafficDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(CanTrafficDescriptor);

CanTrafficDescriptor::CanTrafficDescriptor() : cClassDescriptor("CanTraffic", "cPacket")
{
}

CanTrafficDescriptor::~CanTrafficDescriptor()
{
}

bool CanTrafficDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CanTraffic *>(obj)!=NULL;
}

const char *CanTrafficDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CanTrafficDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int CanTrafficDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *CanTrafficDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int CanTrafficDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CanTrafficDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "short",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *CanTrafficDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "CanTrafficType";
            return NULL;
        default: return NULL;
    }
}

int CanTrafficDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CanTraffic *pp = (CanTraffic *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CanTrafficDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CanTraffic *pp = (CanTraffic *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        default: return "";
    }
}

bool CanTrafficDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CanTraffic *pp = (CanTraffic *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        default: return false;
    }
}

const char *CanTrafficDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *CanTrafficDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CanTraffic *pp = (CanTraffic *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(CanFrame);

CanFrame::CanFrame(const char *name, int kind) : CanTraffic(name,kind)
{
    this->MessageID_var = 0;
    this->Data_var = 0;
    this->frameByteLength_var = 0;
}

CanFrame::CanFrame(const CanFrame& other) : CanTraffic(other)
{
    copy(other);
}

CanFrame::~CanFrame()
{
}

CanFrame& CanFrame::operator=(const CanFrame& other)
{
    if (this==&other) return *this;
    CanTraffic::operator=(other);
    copy(other);
    return *this;
}

void CanFrame::copy(const CanFrame& other)
{
    this->MessageID_var = other.MessageID_var;
    this->Data_var = other.Data_var;
    this->frameByteLength_var = other.frameByteLength_var;
}

void CanFrame::parsimPack(cCommBuffer *b)
{
    CanTraffic::parsimPack(b);
    doPacking(b,this->MessageID_var);
    doPacking(b,this->Data_var);
    doPacking(b,this->frameByteLength_var);
}

void CanFrame::parsimUnpack(cCommBuffer *b)
{
    CanTraffic::parsimUnpack(b);
    doUnpacking(b,this->MessageID_var);
    doUnpacking(b,this->Data_var);
    doUnpacking(b,this->frameByteLength_var);
}

int CanFrame::getMessageID() const
{
    return MessageID_var;
}

void CanFrame::setMessageID(int MessageID)
{
    this->MessageID_var = MessageID;
}

int CanFrame::getData() const
{
    return Data_var;
}

void CanFrame::setData(int Data)
{
    this->Data_var = Data;
}

int CanFrame::getFrameByteLength() const
{
    return frameByteLength_var;
}

void CanFrame::setFrameByteLength(int frameByteLength)
{
    this->frameByteLength_var = frameByteLength;
}

class CanFrameDescriptor : public cClassDescriptor
{
  public:
    CanFrameDescriptor();
    virtual ~CanFrameDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(CanFrameDescriptor);

CanFrameDescriptor::CanFrameDescriptor() : cClassDescriptor("CanFrame", "CanTraffic")
{
}

CanFrameDescriptor::~CanFrameDescriptor()
{
}

bool CanFrameDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CanFrame *>(obj)!=NULL;
}

const char *CanFrameDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CanFrameDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int CanFrameDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *CanFrameDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "MessageID",
        "Data",
        "frameByteLength",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int CanFrameDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='M' && strcmp(fieldName, "MessageID")==0) return base+0;
    if (fieldName[0]=='D' && strcmp(fieldName, "Data")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameByteLength")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CanFrameDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *CanFrameDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int CanFrameDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CanFrame *pp = (CanFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CanFrameDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CanFrame *pp = (CanFrame *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMessageID());
        case 1: return long2string(pp->getData());
        case 2: return long2string(pp->getFrameByteLength());
        default: return "";
    }
}

bool CanFrameDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CanFrame *pp = (CanFrame *)object; (void)pp;
    switch (field) {
        case 0: pp->setMessageID(string2long(value)); return true;
        case 1: pp->setData(string2long(value)); return true;
        case 2: pp->setFrameByteLength(string2long(value)); return true;
        default: return false;
    }
}

const char *CanFrameDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *CanFrameDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CanFrame *pp = (CanFrame *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(CanSendRequest);

CanSendRequest::CanSendRequest(const char *name, int kind) : CanTraffic(name,kind)
{
    this->requestMessageID_var = 0;
}

CanSendRequest::CanSendRequest(const CanSendRequest& other) : CanTraffic(other)
{
    copy(other);
}

CanSendRequest::~CanSendRequest()
{
}

CanSendRequest& CanSendRequest::operator=(const CanSendRequest& other)
{
    if (this==&other) return *this;
    CanTraffic::operator=(other);
    copy(other);
    return *this;
}

void CanSendRequest::copy(const CanSendRequest& other)
{
    this->requestMessageID_var = other.requestMessageID_var;
}

void CanSendRequest::parsimPack(cCommBuffer *b)
{
    CanTraffic::parsimPack(b);
    doPacking(b,this->requestMessageID_var);
}

void CanSendRequest::parsimUnpack(cCommBuffer *b)
{
    CanTraffic::parsimUnpack(b);
    doUnpacking(b,this->requestMessageID_var);
}

int CanSendRequest::getRequestMessageID() const
{
    return requestMessageID_var;
}

void CanSendRequest::setRequestMessageID(int requestMessageID)
{
    this->requestMessageID_var = requestMessageID;
}

class CanSendRequestDescriptor : public cClassDescriptor
{
  public:
    CanSendRequestDescriptor();
    virtual ~CanSendRequestDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(CanSendRequestDescriptor);

CanSendRequestDescriptor::CanSendRequestDescriptor() : cClassDescriptor("CanSendRequest", "CanTraffic")
{
}

CanSendRequestDescriptor::~CanSendRequestDescriptor()
{
}

bool CanSendRequestDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CanSendRequest *>(obj)!=NULL;
}

const char *CanSendRequestDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CanSendRequestDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int CanSendRequestDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *CanSendRequestDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "requestMessageID",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int CanSendRequestDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "requestMessageID")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CanSendRequestDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *CanSendRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int CanSendRequestDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CanSendRequest *pp = (CanSendRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CanSendRequestDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CanSendRequest *pp = (CanSendRequest *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRequestMessageID());
        default: return "";
    }
}

bool CanSendRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CanSendRequest *pp = (CanSendRequest *)object; (void)pp;
    switch (field) {
        case 0: pp->setRequestMessageID(string2long(value)); return true;
        default: return false;
    }
}

const char *CanSendRequestDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *CanSendRequestDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CanSendRequest *pp = (CanSendRequest *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(CanSendPermit);

CanSendPermit::CanSendPermit(const char *name, int kind) : CanTraffic(name,kind)
{
}

CanSendPermit::CanSendPermit(const CanSendPermit& other) : CanTraffic(other)
{
    copy(other);
}

CanSendPermit::~CanSendPermit()
{
}

CanSendPermit& CanSendPermit::operator=(const CanSendPermit& other)
{
    if (this==&other) return *this;
    CanTraffic::operator=(other);
    copy(other);
    return *this;
}

void CanSendPermit::copy(const CanSendPermit& other)
{
}

void CanSendPermit::parsimPack(cCommBuffer *b)
{
    CanTraffic::parsimPack(b);
}

void CanSendPermit::parsimUnpack(cCommBuffer *b)
{
    CanTraffic::parsimUnpack(b);
}

class CanSendPermitDescriptor : public cClassDescriptor
{
  public:
    CanSendPermitDescriptor();
    virtual ~CanSendPermitDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(CanSendPermitDescriptor);

CanSendPermitDescriptor::CanSendPermitDescriptor() : cClassDescriptor("CanSendPermit", "CanTraffic")
{
}

CanSendPermitDescriptor::~CanSendPermitDescriptor()
{
}

bool CanSendPermitDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CanSendPermit *>(obj)!=NULL;
}

const char *CanSendPermitDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CanSendPermitDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int CanSendPermitDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *CanSendPermitDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int CanSendPermitDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CanSendPermitDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *CanSendPermitDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int CanSendPermitDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CanSendPermit *pp = (CanSendPermit *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CanSendPermitDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CanSendPermit *pp = (CanSendPermit *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool CanSendPermitDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CanSendPermit *pp = (CanSendPermit *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *CanSendPermitDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *CanSendPermitDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CanSendPermit *pp = (CanSendPermit *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(CanArbitrationFinish);

CanArbitrationFinish::CanArbitrationFinish(const char *name, int kind) : CanTraffic(name,kind)
{
}

CanArbitrationFinish::CanArbitrationFinish(const CanArbitrationFinish& other) : CanTraffic(other)
{
    copy(other);
}

CanArbitrationFinish::~CanArbitrationFinish()
{
}

CanArbitrationFinish& CanArbitrationFinish::operator=(const CanArbitrationFinish& other)
{
    if (this==&other) return *this;
    CanTraffic::operator=(other);
    copy(other);
    return *this;
}

void CanArbitrationFinish::copy(const CanArbitrationFinish& other)
{
}

void CanArbitrationFinish::parsimPack(cCommBuffer *b)
{
    CanTraffic::parsimPack(b);
}

void CanArbitrationFinish::parsimUnpack(cCommBuffer *b)
{
    CanTraffic::parsimUnpack(b);
}

class CanArbitrationFinishDescriptor : public cClassDescriptor
{
  public:
    CanArbitrationFinishDescriptor();
    virtual ~CanArbitrationFinishDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(CanArbitrationFinishDescriptor);

CanArbitrationFinishDescriptor::CanArbitrationFinishDescriptor() : cClassDescriptor("CanArbitrationFinish", "CanTraffic")
{
}

CanArbitrationFinishDescriptor::~CanArbitrationFinishDescriptor()
{
}

bool CanArbitrationFinishDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CanArbitrationFinish *>(obj)!=NULL;
}

const char *CanArbitrationFinishDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CanArbitrationFinishDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int CanArbitrationFinishDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *CanArbitrationFinishDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int CanArbitrationFinishDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CanArbitrationFinishDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *CanArbitrationFinishDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int CanArbitrationFinishDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CanArbitrationFinish *pp = (CanArbitrationFinish *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CanArbitrationFinishDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CanArbitrationFinish *pp = (CanArbitrationFinish *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool CanArbitrationFinishDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CanArbitrationFinish *pp = (CanArbitrationFinish *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *CanArbitrationFinishDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *CanArbitrationFinishDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CanArbitrationFinish *pp = (CanArbitrationFinish *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(CanFrames);

CanFrames::CanFrames(const char *name, int kind) : CanFrame(name,kind)
{
}

CanFrames::CanFrames(const CanFrames& other) : CanFrame(other)
{
    copy(other);
}

CanFrames::~CanFrames()
{
}

CanFrames& CanFrames::operator=(const CanFrames& other)
{
    if (this==&other) return *this;
    CanFrame::operator=(other);
    copy(other);
    return *this;
}

void CanFrames::copy(const CanFrames& other)
{
}

void CanFrames::parsimPack(cCommBuffer *b)
{
    CanFrame::parsimPack(b);
}

void CanFrames::parsimUnpack(cCommBuffer *b)
{
    CanFrame::parsimUnpack(b);
}

class CanFramesDescriptor : public cClassDescriptor
{
  public:
    CanFramesDescriptor();
    virtual ~CanFramesDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(CanFramesDescriptor);

CanFramesDescriptor::CanFramesDescriptor() : cClassDescriptor("CanFrames", "CanFrame")
{
}

CanFramesDescriptor::~CanFramesDescriptor()
{
}

bool CanFramesDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CanFrames *>(obj)!=NULL;
}

const char *CanFramesDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CanFramesDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int CanFramesDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *CanFramesDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int CanFramesDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CanFramesDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *CanFramesDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int CanFramesDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CanFrames *pp = (CanFrames *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CanFramesDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CanFrames *pp = (CanFrames *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool CanFramesDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CanFrames *pp = (CanFrames *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *CanFramesDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *CanFramesDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CanFrames *pp = (CanFrames *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


