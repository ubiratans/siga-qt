#ifndef CORE_COORDINATE_SYSTEM_COORDINATE_SYSTEM_H
#define CORE_COORDINATE_SYSTEM_COORDINATE_SYSTEM_H

#include <string>

class CoordinateSystem {
public:
  CoordinateSystem();

  std::string name();

  const std::string xAxisName() const;
  const std::string yAxisName() const;

  double top();
  double bottom();
  double left();
  double right();

  double width();
  double height();

  virtual std::pair< double, double > origin() = 0;

protected:
  virtual void initialize() = 0;

  double m_top;
  double m_bottom;
  double m_left;
  double m_right;

  std::string m_name;
};

#endif
