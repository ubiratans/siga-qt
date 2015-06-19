#include "view/gui/translation_utils.h"

#include <QCoreApplication>
#include <QLocale>

const QList< QString > TranslationUtils::m_accepted_languages({"pt_BR", "en_US", "de_DE"});
QTranslator TranslationUtils::m_translator;
std::string TranslationUtils::m_default_context = "";

QString TranslationUtils::translate(const std::string &context, const std::string &key) {
  return QCoreApplication::translate(context.c_str(), key.c_str());
}

QString TranslationUtils::tr(const std::string &key) {
  return translate(m_default_context, key);
}

void TranslationUtils::setDefaultContext(std::string context) {
  m_default_context = context;
}

void TranslationUtils::loadDefaultTranslation() {
  QString system_language = QLocale::system().name();
  QString lang = "en_US";

  if ( m_accepted_languages.contains(system_language) ) {
    lang = system_language;
  }

  loadTranslation(lang);
}

bool TranslationUtils::loadTranslation(QString lang) {
  QString file = "lang/translation_package_" + lang;

  bool status = m_translator.load(file);
  return status && QCoreApplication::installTranslator(&m_translator);
}
