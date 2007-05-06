#ifndef __FOXLIB_H__
#define __FOXLIB_H__

//fox lib interface
//2006.10.10
//QWL1996@GMAIL.COM

namespace fox
{
	class vs_addin
	{
	public:
		virtual int get_version() = 0;
	};
	class vs60_addin : public vs_addin
	{
	public:
		virtual int get_version() { return 0x60;}
		virtual int  get_line_column(const char * file, int line) = 0;
		virtual bool insert_block(const char * file, int line, int column, const char * text) = 0;
		virtual bool replace_text(const char * file, int line, const char * old, const char * text) = 0;
		virtual bool goto_line(const char * file, int line) = 0;
	};
	class vs2005_addin : public vs_addin
	{
	public:
		virtual int get_version() { return 0x2005; }
	};
	namespace ui
	{
		class base
		{
		public:
			virtual ~base() {}
			virtual HWND create(HWND hParent, RECT rc) = 0;
			virtual HWND handle() = 0;
			virtual int get_type() const = 0;
		};

		template <int t_type>
		class base_t : public base
		{
		public:
			virtual int get_type() const
			{
				return t_type;
			}
			static int type() { return t_type; }
		};

		class item : public base_t<0x2000>
		{
		public:
			virtual const char * name() = 0;
		};	

		class vs_item : public item
		{
		public:
			virtual const char * name() = 0;
			virtual void  set_vsaddin(vs_addin *) = 0;
			virtual void  load_project(const char * name, const char * dspfile, bool bAppend) = 0;
		};	
		
		class item_ex : public item, public CMessageFilter
		{
		public:
			virtual int get_type() const
			{
				return type()+0x0100;
			}
		};
		
		class view : public base_t<0x2001>
		{
		public:
			virtual bool add_item(item * p) = 0;
		};	

	} // namespace ui
} // namespace fox

#endif