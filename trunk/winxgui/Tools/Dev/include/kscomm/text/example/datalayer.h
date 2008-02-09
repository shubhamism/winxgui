/* -------------------------------------------------------------------------
//	文件名		：	kso/datalayer.h
//	创建者		：	许式伟
//	创建时间	：	2003-3-20 10:05:41
//	功能描述	：	数据层提供的服务
//
// -----------------------------------------------------------------------*/

// -------------------------------------------------------------------------
/* interface IKDataLayer */

interface IKDataLayer : IUnknown
{
public: // interface
	STDPROC BeginRead(IN BOOL TryOnly = FALSE) PURE;
	STDPROC BeginWrite(IN BOOL TryOnly = FALSE) PURE;
	STDPROC EndRead() PURE;
	STDPROC EndWrite(IN DL_EndWriteMode_Enum Mode) PURE;
	STDPROC Redo(IN INT StepOffset) PURE;
	STDPROC GoStep(IN STEPID StepID) PURE;
	STDPROC QueryState(OUT DL_State_Enum* Value) PURE;
	STDPROC QueryStepID(IN INT StepOffset, OUT STEPID* Value) PURE;
	STDPROC QueryCapacity(IN DL_Capacity_Enum Kind, OUT INT* Value) PURE;
	STDPROC Get_Capacity(IN DL_Capacity_Enum Kind, OUT INT* Values) PURE;
	STDPROC Set_Capacity(IN DL_Capacity_Enum Kind, IN INT Value) PURE;
	STDPROC Get_Root(OUT IKAtom** Value) PURE;
	STDPROC Set_Root(IN IKAtom* Value) PURE;
	STDPROC_(void*) _Handle() PURE;
};

// -------------------------------------------------------------------------
/* interface IKStep */

interface IKStep : IUnknown
{
	STDPROC Get_Count(OUT INT* Count) PURE;
	STDPROC Get_Item(IN INT Index, OUT IKAtom** ppv) PURE;
	STDPROC_(INT) IndexOf(IN IKAtom* Value) PURE;

	STDPROC First(OUT IKAtom** ppv) PURE;
	STDPROC Last(OUT IKAtom** ppv) PURE;
};

// -------------------------------------------------------------------------
