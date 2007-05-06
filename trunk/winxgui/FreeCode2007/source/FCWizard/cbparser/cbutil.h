#ifndef _CBUTIL_H__
#define _CBUTIL_H__
/*
int __cdecl wxMessageBox(class wxString const &,class wxString const &,long,class wxWindow *,int,int)
{
	return 0;
}
*/

struct cbThreadPoolTask
{
	bool TestDestroy()
	{
		return false;
	}
};
/*
inline long __cdecl wxNewId(void)
{
	static long id = 2000;
	return id++;
}
*/
inline wxString GetStringFromArray(const wxArrayString& array, const wxString& separator)
{
    wxString out;
    for (unsigned int i = 0; i < array.GetCount(); ++i)
        out << array[i] << separator;
    return out;
}

inline wxArrayString GetArrayFromString(const wxString& text, const wxString& separator, bool trimSpaces)
{
    wxArrayString out;
    wxString search = text;
    int seplen = separator.Length();
    while (true)
    {
        int idx = search.Find(separator);
        if (idx == -1)
        {
            if (trimSpaces)
            {
                search.Trim(false);
                search.Trim(true);
            }
            if (!search.IsEmpty())
                out.Add(search);
            break;
        }
        wxString part = search.Left(idx);
        search.Remove(0, idx + seplen);
        if (trimSpaces)
        {
            part.Trim(false);
            part.Trim(true);
        }
        if (!part.IsEmpty())
            out.Add(part);
    }
    return out;
}
/*
inline int __cdecl wxMessageBox2(class wxString const & str)
{
	return 0;
}


inline void __cdecl wxAssert(int,char const *,int,char const *,char const *)
{
}
*/

inline bool cbRead(wxFile& file,wxString& st)
{
    st.Empty();
    if (!file.IsOpened())
        return false;
    int len = file.Length();
    if(!len)
    {
        file.Close();
        return true;
    }
#if wxUSE_UNICODE
    char* buff = new char[len+1];
    if (!buff)
    {
        file.Close();
        return false;
    }
    file.Read((void*)buff, len);
    file.Close();
    buff[len]='\0';
    st = wxString((const char *)buff, wxConvUTF8);
    delete[] buff;
#else
    char* buff = st.GetWriteBuf(len); // GetWriteBuf already handles the extra '\0'.
    file.Read((void*)buff, len);
    file.Close();
    st.UngetWriteBuf();
#endif
    return true;
}

inline const wxString cbRead(wxFile& file)
{
    wxString st;
    cbRead(file,st);
    return st;
}


/// Writes a wxString to a non-unicode file. File must be open. File is closed automatically.
inline bool cbWrite(wxFile& file, const wxString& buff)
{
    bool result = false;
    if (file.IsOpened())
    {
        result = file.Write(buff,wxConvUTF8);
        if(result)
            file.Flush();
        file.Close();
    }
    return result;
}

#endif