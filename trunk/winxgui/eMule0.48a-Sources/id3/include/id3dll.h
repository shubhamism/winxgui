#ifndef __id3dll_h__
#define __id3dll_h__

#ifndef _ID3LIB_ID3_H_
#include "../id3lib/include/id3.h"
#endif

ID3_C_EXPORT const Mp3_Headerinfo* CCONV ID3Tag_GetMp3HeaderInfo(const ID3Tag* tag);

ID3_C_EXPORT ID3_TextEnc CCONV ID3Field_GetEncoding(const ID3Field* field);

ID3_C_EXPORT const char* CCONV ID3Frame_GetDescription(const ID3Frame* frame);
ID3_C_EXPORT const char* CCONV ID3Frame_GetTextID(const ID3Frame* frame);

ID3_C_EXPORT char* CCONV ID3_GetStringA(const ID3Frame* frame, ID3_FieldID fldName);
ID3_C_EXPORT void CCONV ID3_FreeStringA(char* p);

#ifdef __cplusplus

//////////////////////////////////////////////////////////////////////

class ID3_Field_ConstPtr
{
protected:
	union
	{
		ID3Field* field;
		const ID3Field* cfield;
	};

public:
	ID3_Field_ConstPtr(const ID3Field* ptr = NULL) {
		cfield = ptr;
	}

	operator const ID3Field*() const {
		return cfield;
	}

	size_t Size() const {
		return ID3Field_Size(field);
	}

	size_t GetNumTextItems() const {
		return ID3Field_GetNumTextItems(field);
	}

	uint32 Get() const {
		return ID3Field_GetINT(field);
	}

	ID3_TextEnc GetEncoding() const
	{
		return ID3Field_GetEncoding(field);
	}

	size_t Get(unicode_t *buffer, size_t maxChars) const
	{
		return ID3Field_GetUNICODE(field, buffer, maxChars);
	}

	size_t Get(unicode_t *buffer, size_t maxChars, size_t itemNum) const
	{
		return ID3Field_GetUNICODEItem(field, buffer, maxChars, itemNum);
	}

	size_t Get(char *buffer, size_t maxChars) const
	{
		return ID3Field_GetASCII(field, buffer, maxChars);
	}

	size_t Get(char *buffer, size_t maxChars, size_t itemNum) const
	{
		return ID3Field_GetASCIIItem(field, buffer, maxChars, itemNum);
	}

	void Get(uchar *buffer, size_t buffLength)
	{
		ID3Field_GetBINARY(field, buffer, buffLength);
	}

	void ToFile(const char *fileName)
	{
		ID3Field_ToFile(field, fileName);
	}
};

class ID3_Field_Ptr : public ID3_Field_ConstPtr
{
public:
	ID3_Field_Ptr(ID3Field* ptr = NULL)
		: ID3_Field_ConstPtr(ptr)
	{
	}

public:
	void Clear()
	{
		ID3Field_Clear(field);
	}

	void Set(uint32 data)
	{
		ID3Field_SetINT(field, data);
	}

	void Set(const unicode_t *string)
	{
		ID3Field_SetUNICODE(field, string);
	}

	void Add(const unicode_t *string)
	{
		ID3Field_AddUNICODE(field, string);
	}

	void Set(const char *string)
	{
		ID3Field_SetASCII(field, string);
	}

	void Add(const char *string)
	{
		ID3Field_AddASCII(field, string);
	}

	void Set(const uchar *data, size_t size)
	{
		ID3Field_SetBINARY(field, data, size);
	}

	void FromFile(const char *fileName)
	{
		ID3Field_FromFile(field, fileName);
	}
};

//////////////////////////////////////////////////////////////////////

class ID3_Tag
{
private:
	ID3Tag* tag;

	ID3_Tag(const ID3_Tag&);
	void operator=(const ID3_Tag&);

public:
	ID3_Tag()
	{
		tag = ID3Tag_New();
	}
	~ID3_Tag()
	{
		ID3Tag_Delete(tag);
	}

	void Clear()
	{
		ID3Tag_Clear(tag);
	}

	bool HasChanged() const
	{
		return ID3Tag_HasChanged(tag);
	}

	void SetUnsync(bool unsync)
	{
		ID3Tag_SetUnsync(tag, unsync);
	}

	void SetExtendedHeader(bool ext)
	{
		ID3Tag_SetExtendedHeader(tag, ext);
	}

	void SetPadding(bool pad)
	{
		ID3Tag_SetPadding(tag, pad);
	}

	const Mp3_Headerinfo* GetMp3HeaderInfo() const
	{
		return ID3Tag_GetMp3HeaderInfo(tag);
	}

	void AddFrame(const ID3Frame *frame)
	{
		ID3Tag_AddFrame(tag, frame);
	}

	bool AttachFrame(ID3Frame *frame)
	{
		return ID3Tag_AttachFrame(tag, frame);
	}

	void AddFrames(const ID3Frame *frames, size_t num)
	{
		ID3Tag_AddFrames(tag, frames, num);
	}

	ID3Frame* RemoveFrame(const ID3Frame *frame)
	{
		return ID3Tag_RemoveFrame(tag, frame);
	}

	ID3_Err Parse(const uchar header[ID3_TAGHEADERSIZE], const uchar *buffer)
	{
		return ID3Tag_Parse(tag, header, buffer);
	}

	size_t Link(const char *fileName)
	{
		return ID3Tag_Link(tag, fileName);
	}

	size_t Link(const char *fileName, flags_t flags)
	{
		return ID3Tag_LinkWithFlags(tag, fileName, flags);
	}

	ID3_Err Update()
	{
		return ID3Tag_Update(tag);
	}

	ID3_Err Update(flags_t type)
	{
		return ID3Tag_UpdateByTagType(tag, type);
	}

	ID3_Err Strip(flags_t ulTagFlags)
	{
		return ID3Tag_Strip(tag, ulTagFlags);
	}

	ID3Frame* Find(ID3_FrameID id) const
	{
		return ID3Tag_FindFrameWithID(tag, id);
	}

	ID3Frame* Find(ID3_FrameID id, ID3_FieldID fld, uint32 data) const
	{
		return ID3Tag_FindFrameWithINT(tag, id, fld, data);
	}

	ID3Frame* Find(ID3_FrameID id, ID3_FieldID fld, const char *data) const
	{
		return ID3Tag_FindFrameWithASCII(tag, id, fld, data);
	}

	ID3Frame* Find(ID3_FrameID id, ID3_FieldID fld, const unicode_t* data) const
	{
		return ID3Tag_FindFrameWithUNICODE(tag, id, fld, data);
	}

	size_t NumFrames() const
	{
		return ID3Tag_NumFrames(tag);
	}

	bool HasTagType(ID3_TagType tt) const
	{
		return ID3Tag_HasTagType(tag, tt);
	}
	
	ID3TagIterator* CreateIterator()
	{
		return ID3Tag_CreateIterator(tag);
	}

	ID3TagConstIterator* CreateIterator() const
	{
		return ID3Tag_CreateConstIterator(tag);
	}
};

//////////////////////////////////////////////////////////////////////

class ID3Tag_Iterator
{
private:
	ID3TagIterator* iter;

	ID3Tag_Iterator(const ID3Tag_Iterator&);
	void operator=(const ID3Tag_Iterator&);

public:
	ID3Tag_Iterator(ID3TagIterator* ptr) : iter(ptr) {}
	~ID3Tag_Iterator() {
		ID3TagIterator_Delete(iter);
	}

	ID3Frame* GetNext()
	{
		return ID3TagIterator_GetNext(iter);
	}
};

class ID3Tag_ConstIterator
{
private:
	ID3TagConstIterator* iter;

	ID3Tag_ConstIterator(const ID3Tag_ConstIterator&);
	void operator=(const ID3Tag_ConstIterator&);

public:
	ID3Tag_ConstIterator(ID3TagConstIterator* ptr) : iter(ptr) {}
	~ID3Tag_ConstIterator() {
		ID3TagConstIterator_Delete(iter);
	}

	const ID3Frame* GetNext() const
	{
		ID3TagConstIterator_GetNext(iter);
	}
};

//////////////////////////////////////////////////////////////////////

class ID3_Frame_ConstPtr
{
protected:
	union
	{
		ID3Frame* frame;
		const ID3Frame* cframe;
	};

public:
	ID3_Frame_ConstPtr(const ID3Frame* ptr = NULL) {
		cframe = ptr;
	}

	operator const ID3Frame*() const
	{
		return cframe;
	}

	ID3_Field_Ptr GetField(ID3_FieldID name) const
	{
		return ID3Frame_GetField(frame, name);
	}

	ID3_FrameID GetID() const
	{
		return ID3Frame_GetID(frame);
	}

	bool GetCompression() const
	{
		return ID3Frame_GetCompression(frame);
	}

	const char* GetDescription() const
	{
		return ID3Frame_GetDescription(frame);
	}

	const char* GetTextID() const
	{
		return ID3Frame_GetTextID(frame);
	}
};

class ID3_Frame_Ptr : public ID3_Frame_ConstPtr
{
public:
	ID3_Frame_Ptr(ID3Frame* ptr = NULL)
		: ID3_Frame_ConstPtr(ptr)
	{
	}

	operator ID3Frame*() const
	{
		return frame;
	}

	void Clear()
	{
		ID3Frame_Clear(frame);
	}

	void SetID(ID3_FrameID id)
	{
		ID3Frame_SetID(frame, id);
	}

	void SetCompression(bool comp)
	{
		ID3Frame_SetCompression(frame, comp);
	}
};

class ID3_Frame : public ID3_Frame_Ptr
{
private:
	ID3_Frame(const ID3_Frame&);
	void operator=(const ID3_Frame&);

public:
	ID3_Frame(ID3Frame* ptr) : ID3_Frame_Ptr(ptr) {}
	ID3_Frame()
	{
		frame = ID3Frame_New();
	}
	ID3_Frame(ID3_FrameID id)
	{
		frame = ID3Frame_NewID(id);
	}
	~ID3_Frame()
	{
		ID3Frame_Delete(frame);
	}
};

//////////////////////////////////////////////////////////////////////

#endif // __cplusplus

#endif
