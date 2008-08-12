#ifndef LINK_H
#define LINK_H

#include <GeneralDefinitions.h>

//Abstract class for a node in a linked list (not to confuse with GenericNode, which is the same, just templated)
class LinkClass
{
public:
	//Destructor
	virtual ~LinkClass()
		{ THISCALL(0x5565A0); }

	//LinkClass
	virtual LinkClass* GetNext()
		{ return Next; }

	virtual LinkClass* GetPrevious()
		{ return Previous; }

	virtual LinkClass* AddBeforeMe(LinkClass* pLink)	//adds pLink to the list, one node before this
														//returns first node of the list
		{
			IsolateFromList();
			
			Next = pLink->get_Next();
			Previous = pLink;
			
			pLink->set_Next(this);
			
			if(Next)
				Next->set_Previous(this);
			
			return GetFirst();
		}

	virtual LinkClass* PutAtEndOf(LinkClass* pLink)	//puts this at the end of the list pLink is in
													//returns first node of that list
		{
			IsolateFromList();
			
			LinkClass* pLast = pLink->GetLast();

			pLast->set_Next(this);
			Previous = pLast;
			Next = NULL;

			return GetFirst();
		}

	virtual LinkClass* PutAtBeginningOf(LinkClass* pLink)	//puts this at the beginning of the list pLink is in
														//returns first node of that list (this)
		{
			IsolateFromList();
			
			LinkClass* pFirst = pLink->GetFirst();

			pFirst->set_Previous(this);
			Next = pFirst;
			Previous = NULL;

			return this;
		}

	virtual LinkClass* GetFirst()	//finds the first node in the list
		{
			LinkClass* p = this;

			while(p->get_Previous())
			{
				p = p->get_Previous();

				if(p == this)
					return this;
			}
			return p;
		}

	virtual LinkClass* GetLast()	//finds the last node in the list
		{
			LinkClass* p = this;

			while(p->get_Next())
			{
				p = p->get_Next();

				if(p == this)
					return this;
			}
			return p;
		}

	virtual void Isolate()	//removes this from the list
		{
			Next = NULL;
			Previous = NULL;
		}

	virtual LinkClass* IsolateFromList()	//removes this from the list
											//returns first node if possible
		{
			LinkClass* pFirst = GetFirst();
			LinkClass* pLast = GetLast();

			if(Next)
				Next->set_Previous(Previous);
				
			if(Previous)
				Previous->set_Next(Next);
				
			Previous = NULL;
			Next = NULL;

			if(pFirst != this)
				return pFirst;
			else if(pLast != this)
				return pLast->GetFirst();
			else
				return NULL;
		}

	//Properties
	PROPERTY(LinkClass*,	Next);
	PROPERTY(LinkClass*,	Previous);
};

#endif
