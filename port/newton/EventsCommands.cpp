#include "EventsCommands.h"
#include "BluntServer.h"
#include "BluntClient.h"

BluntEvent::BluntEvent(BluntEventType type, NewtonErr result)
{
    fAEventID = kBluntEventId;
    fAEventClass = kBluntEventClass;
    fOriginalEvent = this;
    fType = type;
    fResult = result;
    fDelete = false;
}

void BluntResetCompleteEvent::Process(BluntClient *client)
{
    client->ResetComplete(fResult);
}

BluntInquiryResultEvent::BluntInquiryResultEvent(NewtonErr result):
    BluntEvent(E_INQUIRY_RESULT, result)
{
}

BluntLinkKeyNotificationEvent::BluntLinkKeyNotificationEvent(NewtonErr result, UByte *addr, UByte *key):
    BluntEvent(E_LINK_KEY_NOTIFICATION, result)
{
    if(result == noErr) {
        memcpy(fBdAddr, addr, 6);
        memcpy(fLinkKey, key, 16);
    }
}

BluntNameRequestResultEvent::BluntNameRequestResultEvent(NewtonErr result, UChar* name, UByte* addr):
    BluntEvent(E_NAME_REQUEST_RESULT, result)
{
    strncpy((Char*) fName,(Char*) name, 64);
    fName[63] = 0;
    memcpy(fBdAddr, addr, 6);
}

BluntCommandCompleteEvent::BluntCommandCompleteEvent(NewtonErr result, ULong s):
    BluntEvent(E_COMMAND_COMPLETE, result)
{
    fStatus = s;
}

BluntConnectionCompleteEvent::BluntConnectionCompleteEvent(NewtonErr s):
    BluntEvent(E_CONNECTION_COMPLETE, s)
{
}

BluntDisconnectCompleteEvent::BluntDisconnectCompleteEvent(NewtonErr s):
    BluntEvent(E_DISCONNECT_COMPLETE, s)
{
}

BluntCommand::BluntCommand()
{
    fOriginalCommand = this;
    fDelete = false;
}

void BluntStartCommand::Process(BluntServer *server)
{
    server->Start();
}

void BluntInquiryCommand::Process(BluntServer *server)
{
    server->InquiryStart(this);
}

void BluntInquiryCancelCommand::Process(BluntServer *server)
{
    server->InquiryCancel(this);
}

void BluntStopCommand::Process(BluntServer *server)
{
    server->Stop();
}
