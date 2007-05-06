
FCWizardps.dll: dlldata.obj FCWizard_p.obj FCWizard_i.obj
	link /dll /out:FCWizardps.dll /def:FCWizardps.def /entry:DllMain dlldata.obj FCWizard_p.obj FCWizard_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del FCWizardps.dll
	@del FCWizardps.lib
	@del FCWizardps.exp
	@del dlldata.obj
	@del FCWizard_p.obj
	@del FCWizard_i.obj
