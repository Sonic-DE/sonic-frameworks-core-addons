#include "kpluginfactory.h"

class SimplePluginClass : public QObject
{
    Q_OBJECT

public:
    explicit SimplePluginClass(QObject *parent, const QVariantList &args)
    {
    }
};

K_PLUGIN_CLASS_WITH_JSON(SimplePluginClass, "jsonplugin.json")

#include "kpluginclass.moc"
