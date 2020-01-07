// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ****************************************************************************
//  File: DisplacePluginInfo.h
// ****************************************************************************

#ifndef DISPLACE_PLUGIN_INFO_H
#define DISPLACE_PLUGIN_INFO_H
#include <OperatorPluginInfo.h>
#include <operator_plugin_exports.h>

class DisplaceAttributes;

// ****************************************************************************
//  Class: DisplacePluginInfo
//
//  Purpose:
//    Five classes that provide all the information about an Displace operator
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
//  Modifications:
//
// ****************************************************************************

class DisplaceGeneralPluginInfo : public virtual GeneralOperatorPluginInfo
{
  public:
    virtual const char *GetName() const;
    virtual const char *GetVersion() const;
    virtual const char *GetID() const;
    virtual bool  EnabledByDefault() const;
    virtual const char *GetCategoryName() const;
};

class DisplaceCommonPluginInfo : public virtual CommonOperatorPluginInfo, public virtual DisplaceGeneralPluginInfo
{
  public:
    virtual AttributeSubject *AllocAttributes();
    virtual void CopyAttributes(AttributeSubject *to, AttributeSubject *from);
};

class DisplaceGUIPluginInfo : public virtual GUIOperatorPluginInfo, public virtual DisplaceCommonPluginInfo
{
  public:
    virtual QString *GetMenuName() const;
    virtual QvisPostableWindowObserver *CreatePluginWindow(int type,
        AttributeSubject *attr, const QString &caption, const QString &shortName,
        QvisNotepadArea *notepad);
    virtual const char **XPMIconData() const;
};

class DisplaceViewerEnginePluginInfo : public virtual ViewerEngineOperatorPluginInfo, public virtual DisplaceCommonPluginInfo
{
  public:
    virtual AttributeSubject *GetClientAtts();
    virtual AttributeSubject *GetDefaultAtts();
    virtual void SetClientAtts(AttributeSubject *atts);
    virtual void GetClientAtts(AttributeSubject *atts);

    virtual void InitializeOperatorAtts(AttributeSubject *atts,
                                        const avtPlotMetaData &plot,
                                        const bool fromDefault);
    virtual void UpdateOperatorAtts(AttributeSubject *atts,
                                    const avtPlotMetaData &plot);
    virtual const char *GetMenuName() const;

    static void InitializeGlobalObjects();
  private:
    static DisplaceAttributes *defaultAtts;
    static DisplaceAttributes *clientAtts;
};

class DisplaceViewerPluginInfo : public virtual ViewerOperatorPluginInfo, public virtual DisplaceViewerEnginePluginInfo
{
  public:
    virtual const char **XPMIconData() const;
};

class DisplaceEnginePluginInfo : public virtual EngineOperatorPluginInfo, public virtual DisplaceViewerEnginePluginInfo
{
  public:
    virtual avtPluginFilter *AllocAvtPluginFilter();
};

class DisplaceScriptingPluginInfo : public virtual ScriptingOperatorPluginInfo, public virtual DisplaceCommonPluginInfo
{
  public:
    virtual void InitializePlugin(AttributeSubject *subj, void *data);
    virtual void *GetMethodTable(int *nMethods);
    virtual bool TypesMatch(void *pyobject);
    virtual char *GetLogString();
    virtual void SetDefaults(const AttributeSubject *atts);
};

#endif
