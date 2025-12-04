// Bu blok "Header Guard" olarak bilinir. Bu dosyanın defalarca eklenip hata vermesini önler.
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt'nin hazır kütüphanelerini projeye dahil ediyoruz.
#include <QMainWindow>   // Ana pencereyi oluşturmak için gerekli temel sınıf.
#include <QLabel>        // Ekrana resim veya yazı koymak için (Patlama efekti vs.).
#include <QPushButton>   // Raket olarak kullanacağımız buton için.
#include <QTimer>        // Oyunun sürekli akmasını sağlayan zamanlayıcı için.
#include <QMouseEvent>   // Fare hareketlerini (tıklama, sürükleme) algılamak için.
#include <QResizeEvent>  // Pencere boyutu değişirse her şeyi düzeltmek için.
#include "top.h"         // Kendi yazdığımız "Top" sınıfını buraya tanıtıyoruz[cite: 1].

// Qt'nin kendi standart namespace (isim uzayı) tanımlamaları.
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// MainWindow sınıfını oluşturuyoruz ve QMainWindow'dan miras alıyoruz (onun özelliklerini taşıyor).
class MainWindow : public QMainWindow
{
    Q_OBJECT // BU ÇOK ÖNEMLİ HACI: Sinyal ve Slot (Signal-Slot) mekanizmasının çalışması için bu makro şarttır.

public:
    // Yapıcı Fonksiyon (Constructor): Pencere ilk açıldığında çalışacak kodlar burada.
    MainWindow(QWidget *parent = nullptr);

    // Yıkıcı Fonksiyon (Destructor): Pencere kapatıldığında belleği temizlemek için çalışır.
    ~MainWindow();

protected:
    // --- OLAY YÖNETİMİ (EVENT HANDLING) ---
    // Bu fonksiyonlar normalde Qt'de var ama biz onları "override" ediyoruz (yani eziyoruz/kendi isteğimize göre değiştiriyoruz).

    // Fareye tıklandığında ne olsun? (Raketi tutmak için)
    void mousePressEvent(QMouseEvent *event) override;

    // Fare hareket ettiğinde ne olsun? (Raketi sürüklemek için)
    void mouseMoveEvent(QMouseEvent *event) override;

    // Fare bırakıldığında ne olsun? (Raketi bırakmak için)
    void mouseReleaseEvent(QMouseEvent *event) override;

    // Pencere boyutu elle değiştirilirse ne olsun? (Raketin aşağıda sabit kalması için)
    void resizeEvent(QResizeEvent *event) override;

public slots:
    // --- OYUN DÖNGÜSÜ ---
    // Zamanlayıcı (Timer) her dolduğunda bu fonksiyon çalışacak.
    // Topun hareketi, çarpışma kontrolleri vs. hepsi burada.
    void oyunHareketleri();

private:
    // Arayüz elemanlarına (UI) ulaşmamızı sağlayan işaretçi.
    Ui::MainWindow *ui;

    // --- OYUN NESNELERİ ---
    QTimer *zamanlayici; // Oyunun kalbi, sürekli atarak oyunu ilerletir.
    Top *top;            // Bizim top nesnemiz (top.h dosyasından geliyor).

    QPushButton *buton;  // Raket görevi gören buton.
    QLabel *patlama;     // Oyun bittiğinde çıkacak patlama resmi.

    // --- KOORDİNAT VE HAREKET DEĞİŞKENLERİ ---
    int topX, topY;      // Topun o anki X (yatay) ve Y (dikey) konumu.
    int adimX, adimY;    // Topun hızı ve yönü (Örn: +3 sağa, -3 sola).
    int skor;            // Oyuncunun puanı.

    // --- FARE KONTROL DEĞİŞKENLERİ ---
    int butonMesafe;     // Butonun (raketin) alt kenardan ne kadar yukarıda duracağı.
    bool tutusVarMi;     // Kullanıcı şu an raketi tutuyor mu? (True/False).
    int fareFarki;       // Farenin tıkladığı yer ile butonun sol köşesi arasındaki fark (Düzgün sürükleme için).
};
#endif // MAINWINDOW_H bitişi
