#ifndef VIEW_TRANSLATION_UTILS_H
#define VIEW_TRANSLATION_UTILS_H

#include <QString>
#include <string>
#include <QLocale>
#include <QTranslator>

class TranslationUtils {
public:
  static QString translate(const std::string &context, const std::string &key);
  static QString tr(const std::string &key); //!< translates using the default context
  static void setDefaultContext(std::string context);

  static bool loadTranslation(QString lang);
  static void loadDefaultTranslation();

private:
  static QTranslator m_translator;
  static const QList< QString > m_accepted_languages;
  static std::string m_default_context;
};

#endif
