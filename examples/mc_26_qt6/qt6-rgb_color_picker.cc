// © 2024 : github.com/NMoroney
// MIT License 
//

#include <QApplication>
#include <QFile>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QSlider>
#include <QString>
#include <QWidget>


class RGBColorPicker : public QWidget {

  public:
    explicit RGBColorPicker(QWidget* parent = 0);

  private:
    int patch_size_px { 100 };
    QPixmap pix_map;

};

RGBColorPicker::RGBColorPicker(QWidget* parent) : QWidget(parent) {

  setFixedSize(400, 170);
  setWindowTitle ("RGB Color Picker");

  QImage rgb(patch_size_px, patch_size_px, QImage::Format_RGB888);
  QLabel* image_label = new QLabel("", this);
  image_label->setGeometry(275, 15, patch_size_px, patch_size_px);


  QLabel* red_value   = new QLabel("", this);
  QLabel* green_value = new QLabel("", this);
  QLabel* blue_value  = new QLabel("", this);

  QSlider* red_slider   = new QSlider(Qt::Horizontal, this);
  QSlider* green_slider = new QSlider(Qt::Horizontal, this);
  QSlider* blue_slider  = new QSlider(Qt::Horizontal, this);


  QLabel* red_label = new QLabel("Red : ", this);
  red_label->setGeometry(10, 10, 50, 30);

  red_slider->setMinimum(0);
  red_slider->setMaximum(255);
  red_slider->setValue(128);
  red_slider->setGeometry(60, 15, 150, 30);
  QObject::connect(red_slider, &QAbstractSlider::valueChanged, [=]() {
    red_value->setText(QString::number(red_slider->value()));
    QColor updated_rgb(red_slider->value(), green_slider->value(), blue_slider->value(), 255);;
    QImage rgb(patch_size_px, patch_size_px, QImage::Format_RGB888);
    rgb.fill(updated_rgb.toRgb());
    QPixmap pix_map;
    pix_map.convertFromImage(rgb);
    image_label->setPixmap(pix_map);
  });


  QLabel* green_label = new QLabel("Green : ", this);
  green_label->setGeometry(10, 50, 50, 30);

  green_slider->setMinimum(0);
  green_slider->setMaximum(255);
  green_slider->setValue(128);
  green_slider->setGeometry(60, 55, 150, 30);
  QObject::connect(green_slider, &QAbstractSlider::valueChanged, [=]() {
    green_value->setText(QString::number(green_slider->value()));
    QColor updated_rgb(red_slider->value(), green_slider->value(), blue_slider->value(), 255);;
    QImage rgb(patch_size_px, patch_size_px, QImage::Format_RGB888);
    rgb.fill(updated_rgb);
    pix_map.convertFromImage(rgb);
    image_label->setPixmap(pix_map);
  });


  QLabel* blue_label = new QLabel("Blue : ", this);
  blue_label->setGeometry(10, 90, 50, 30);

  blue_slider->setMinimum(0);
  blue_slider->setMaximum(255);
  blue_slider->setValue(128);
  blue_slider->setGeometry(60, 95, 150, 30);
  QObject::connect(blue_slider, &QAbstractSlider::valueChanged, [=]() {
    blue_value->setText(QString::number(blue_slider->value()));
    QColor updated_rgb(red_slider->value(), green_slider->value(), blue_slider->value(), 255);;
    QImage rgb(patch_size_px, patch_size_px, QImage::Format_RGB888);
    rgb.fill(updated_rgb.toRgb());
    QPixmap pix_map;
    pix_map.convertFromImage(rgb);
    image_label->setPixmap(pix_map);
  });


  red_value->setText(QString::number(red_slider->value()));
  red_value->setGeometry(230, 10, 50, 30);

  green_value->setText(QString::number(green_slider->value()));
  green_value->setGeometry(230, 50, 50, 30);

  blue_value->setText(QString::number(blue_slider->value()));
  blue_value->setGeometry(230, 90, 50, 30);

  QColor color(green_slider->value(), green_slider->value(), green_slider->value(), 255);
  rgb.fill(color.toRgb());
  pix_map.convertFromImage(rgb);
  image_label->setPixmap(pix_map);

  QPushButton* quit = new QPushButton("Quit", this);
  quit->setGeometry(325, 130, 50, 30);
  QObject::connect(quit, &QPushButton::clicked, [=]() {
    QCoreApplication::quit();
  });

}


int main(int argc, char **argv) {

  QApplication app (argc, argv);

  RGBColorPicker rgb_color_picker;
  rgb_color_picker.show();

  return app.exec();
}

