#include "mainwindow.h"     // MainWindow sınıfının (tanımlar ve değişkenler) bulunduğu başlık dosyasını dahil et.
#include "ui_mainwindow.h"  // Qt Designer ile oluşturulan arayüz (UI) elemanlarına erişmek için gerekli başlık.
#include <QRandomGenerator> // Topun başlangıç konumunu ve yönünü rastgele belirlemek için gerekli kütüphane.

// Yapıcı Fonksiyon (Constructor): MainWindow nesnesi oluşturulduğunda ilk çalışan fonksiyondur.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) // Arayüz nesnesini dinamik olarak oluştur.
{
    ui->setupUi(this); // Arayüz tasarımını (mainwindow.ui) yükle ve ekrana yerleştir.

    // --- RAKET (QPushButton) OLUŞTURULMASI VE AYARLARI ---
    buton = new QPushButton(this); // Ana pencereye ait (this) yeni bir buton oluştur.
    buton->resize(100, 40);        // Butonun genişliğini 100, yüksekliğini 40 piksel yap.
    buton->setText("0");           // Butonun üzerindeki yazıyı başlangıç skoru olan "0" olarak ayarla.
    buton->show();                 // Butonu görünür yap.

    // KRİTİK AYAR: Butonun kendi mouse tıklama olaylarını (basılma efekti gibi) engelle.
    // Kontrolü MainWindow'un mouse olaylarına bırak.
    buton->setAttribute(Qt::WA_TransparentForMouseEvents);

    butonMesafe = 60; // Raketin pencerenin altından 60 piksel yukarıda duracağını belirle.

    // Butonun başlangıç konumunu ayarla:
    // Yatayda ortala: (Pencere Genişliği - Buton Genişliği) / 2
    // Dikeyde alttan 'butonMesafe' kadar yukarıya yerleştir.
    buton->setGeometry((this->width() - buton->width()) / 2,
                       this->height() - butonMesafe,
                       buton->width(),
                       buton->height());

    // --- TOP VE PATLAMA NESNELERİNİN OLUŞTURULMASI ---
    top = new Top(this); // Özel Top sınıfımızdan yeni bir nesne oluştur.

    patlama = new QLabel(this); // Patlama resmi için bir etiket (QLabel) oluştur.
    patlama->setPixmap(QPixmap(":/resimler/resimler/patlamis.png")); // Resim kaynağından patlama resmini yükle.
    patlama->setScaledContents(true); // Resmi etiketin boyutuna sığdır.
    patlama->setGeometry(0, 0, 80, 80); // Patlama etiketinin başlangıç boyutunu ayarla.
    patlama->setVisible(false); // Başlangıçta patlama görünür olmasın (gizli kalsın).

    // --- OYUN DEĞİŞKENLERİNİN BAŞLANGIÇ DEĞERLERİ ---
    skor = 0; // Skoru sıfırla.
    tutusVarMi = false; // Raket şu an tutulmuyor.

    // --- RASTGELE BAŞLANGIÇ KONUMU VE YÖNÜ ---
    topX = QRandomGenerator::global()->bounded(20, 400); // Topun başlangıç X konumunu rastgele ata.
    topY = QRandomGenerator::global()->bounded(20, 150); // Topun başlangıç Y konumunu rastgele ata.

    // adimX: Rastgele sağa (3) veya sola (-3) başlangıç yönü belirle.
    adimX = (QRandomGenerator::global()->bounded(0, 2) == 0) ? 3 : -3;
    adimY = 3; // adimY: Topun aşağı doğru (pozitif) hareket etmesini sağla.

    top->setGeometry(topX, topY, top->width(), top->height()); // Topu belirlenen konuma yerleştir.

    // --- MOUSE İZLEME VE ZAMANLAYICI AYARLARI ---
    setMouseTracking(true); // Pencerenin mouse hareketlerini sürekli olarak izle.
    ui->centralwidget->setMouseTracking(true); // Merkezi widget'ın da mouse hareketlerini izle.

    zamanlayici = new QTimer(this); // Oyun döngüsü için zamanlayıcı nesnesi oluştur.
    // Zamanlayıcının "timeout" sinyali, MainWindow'un "oyunHareketleri" slot'unu tetiklesin.
    connect(zamanlayici, &QTimer::timeout, this, &MainWindow::oyunHareketleri);
    zamanlayici->start(20); // 20 milisaniyede bir oyun döngüsünü çalıştır (50 FPS).
}

// Yıkıcı Fonksiyon (Destructor): Pencere kapanırken bellek temizliğini yapar.
MainWindow::~MainWindow()
{
    delete ui; // Arayüz pointer'ını sil (Qt Designer elemanlarının temizliği).
}

// --- OYUN DÖNGÜSÜ (GAME LOOP) FONKSİYONU ---
void MainWindow::oyunHareketleri()
{
    // --- Topun Hareketi ---
    topX += adimX; // Topun X (yatay) konumunu hız (adimX) kadar artır.
    topY += adimY; // Topun Y (dikey) konumunu hız (adimY) kadar artır.

    // --- Duvar Çarpışmaları (Sekme Fiziği) ---
    // Sağ Duvar: Top pencerenin sağ kenarına çarparsa.
    if (topX + top->width() >= this->width()) adimX = -3; // Yönü tersine (sola) çevir.

    // Sol Duvar: Top pencerenin sol kenarına çarparsa.
    if (topX <= 0) adimX = 3; // Yönü tersine (sağa) çevir.

    // Tavan: Top pencerenin üst kenarına çarparsa.
    if (topY <= 0) adimY = 3; // Yönü tersine (aşağıya) çevir.

    // --- Raket (Buton) Çarpışması ---
    // 1. Top ile buton geometrik olarak kesişiyor mu (intersects) VE top aşağı doğru iniyor mu?
    if (top->geometry().intersects(buton->geometry()) && adimY > 0) {
        // 2. Ek kontrol: Topun alt kenarı, butonun üst kenarına ulaştı mı?
        if (topY + top->height() >= buton->y()) {
            adimY = -3; // Topu yukarı sektir (Yönü tersine çevir).
            skor++;     // Skoru bir artır.
            buton->setText(QString::number(skor)); // Yeni skoru butonun üzerinde göster.
        }
    }

    // --- Oyun Bitişi (Yanma/Game Over) ---
    // Topun alt kenarı pencerenin yüksekliğini geçerse (Yere düşerse)
    if (topY + top->height() >= this->height()) {
        zamanlayici->stop(); // Oyunu durdur.
        top->setVisible(false); // Topu gizle.

        // Patlama efektini topun düştüğü konuma yakın bir yere yerleştir.
        patlama->setGeometry(topX - 15,
                             this->height() - patlama->height(),
                             patlama->width(),
                             patlama->height());
        patlama->setVisible(true); // Patlama resmini görünür yap.
    } else {
        // Oyun devam ediyorsa, topun yeni konumunu uygula.
        top->setGeometry(topX, topY, top->width(), top->height());
    }
}

// --- KULLANICI KONTROLÜ (MOUSE OLAYLARI) ---

// 1. Mouse'a Tıklama Olayı (mousePressEvent)
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) { // Sol tuşa basıldıysa
        if (buton->geometry().contains(event->pos())) { // Tıklanan koordinat butonun içinde mi?
            tutusVarMi = true; // Raket tutuluyor bayrağını doğru yap.
            // Fare ile butonun sol kenarı arasındaki farkı hesapla (fareFarki).
            // Bu, butonu tam ortasından değil, tıkladığın yerden sürüklemeyi sağlar.
            fareFarki = event->x() - buton->x();
        }
    }
}

// 2. Mouse'u Sürükleme Olayı (mouseMoveEvent)
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // Eğer raket tutuluyorsa VE oyun devam ediyorsa:
    if (tutusVarMi && zamanlayici->isActive()) {
        // Yeni X konumu = Farenin X konumu - başlangıçtaki tıklama farkı.
        int yeniX = event->x() - fareFarki;

        // --- Sınır Kontrolü (Raketin ekranda kalması) ---
        if(yeniX < 0) yeniX = 0; // Raket sol kenardan dışarı çıkmasın.
        // Raket sağ kenardan dışarı çıkmasın. (Pencere genişliği - Buton genişliği)
        if(yeniX > this->width() - buton->width()) yeniX = this->width() - buton->width();

        // Butonu yeni X konumuna yerleştir (Y konumu sabit kalır).
        buton->setGeometry(yeniX,
                           this->height() - butonMesafe,
                           buton->width(),
                           buton->height());
    }
}

// 3. Mouse'u Bırakma Olayı (mouseReleaseEvent)
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) { // Sol tuş bırakıldıysa
        tutusVarMi = false; // Tutma bayrağını yanlış yap.
    }
}

// 4. Pencere Boyutunu Değiştirme Olayı (resizeEvent)
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(buton) {
        // Butonu, pencere boyutu değişse bile, mevcut X konumunda ve alttan sabit mesafede tut.
        buton->setGeometry(buton->x(),
                           this->height() - butonMesafe,
                           buton->width(),
                           buton->height());
    }
    QMainWindow::resizeEvent(event); // Temel sınıfın resize olayını da çağır.
}
