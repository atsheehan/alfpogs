#include "MessageHandler.h"

//static member initialization
//next message id(static)
MSGID CMessageHandler::s_NextMSGID=0;

//msgid: add child(static)
MSGID CMessageHandler::MSGID_AddChild=CMessageHandler::GetNextMSGID();

//msgid: remove child(static)
MSGID CMessageHandler::MSGID_RemoveChild=CMessageHandler::GetNextMSGID();

//constructor
CMessageHandler::CMessageHandler(CMessageHandler* pmhParent):
m_pmhParent(NULL)//initialize parent to NULL
{
	//set parent
	SetParent(pmhParent);
}

//destructor
CMessageHandler::~CMessageHandler()
{
	//set parent to NULL
	SetParent(NULL);
}

//set parent
void CMessageHandler::SetParent(CMessageHandler* pmhNewParent)
{
	//does this object have a parent?
	if(HasParent())
	{
		//tell parent we are being removed
		SendMessage(MSGID_RemoveChild,(MSGPARM)GetParent(),(MSGPARM)this);
	}

	//set new parent
	m_pmhParent=pmhNewParent;

	//does this object have a parent
	if(HasParent())
	{
		//tell parent we are being added
		SendMessage(MSGID_AddChild,(MSGPARM)GetParent(),(MSGPARM)this);
	}
}

//get parent
CMessageHandler* CMessageHandler::GetParent()
{
	//return the parent
	return(m_pmhParent);
}

//has parent?
bool CMessageHandler::HasParent()
{
	//return true if parent is non-null
	return(GetParent()!=NULL);
}

//send message
bool CMessageHandler::SendMessage(MSGID MsgID,MSGPARM Parm1,MSGPARM Parm2,MSGPARM Parm3,MSGPARM Parm4)
{
	//attempt to process message
	if(OnMessage(MsgID,Parm1,Parm2,Parm3,Parm4))
	{
		//message has been processed
		return(true);
	}
	else
	{
		//message has not been processed
		//check for a parent
		if(HasParent())
		{
			//parent exists, send message to parent
			return(GetParent()->SendMessage(MsgID,Parm1,Parm2,Parm3,Parm4));
		}
		else
		{
			//parent does not exist, message cannot be processed
			return(false);
		}
	}
}

//process message(pure virtual)
bool CMessageHandler::OnMessage(MSGID MsgID,MSGPARM Parm1,MSGPARM Parm2,MSGPARM Parm3,MSGPARM Parm4)
{
	//process add child message
	if(MsgID==MSGID_AddChild)
	{
		//check that this is the parent
		if(this==(CMessageHandler*)Parm1)
		{
			//this is the parent
			OnAddChild((CMessageHandler*)Parm2);
			return(true);
		}
		else
		{
			//this is not the parent
			return(false);
		}
	}
	else
	//process remove child message
	if(MsgID==MSGID_RemoveChild)
	{
		//check that this is the parent
		if(this==(CMessageHandler*)Parm1)
		{
			//this is the parent
			OnRemoveChild((CMessageHandler*)Parm2);
			return(true);
		}
		else
		{
			//this is not the parent
			return(false);
		}
	}
	else
	//unknown message
	{
		//return false
		return(false);
	}
}

//get next message id(static)
MSGID CMessageHandler::GetNextMSGID()
{
	//return current messageid, and increment value
	return(s_NextMSGID++);
}

//add child handler
void CMessageHandler::OnAddChild(CMessageHandler* pmhChild)
{
	//do nothing
}

//remove child handler
void CMessageHandler::OnRemoveChild(CMessageHandler* pmhChild)
{
	//do nothing
}
