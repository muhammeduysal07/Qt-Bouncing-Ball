🏓 Qt Seken Top Oyunu (Bouncing Ball Game)
Bu proje, C++ ve Qt Framework kullanılarak geliştirilmiş tek kişilik, etkileşimli bir masaüstü oyunudur. Kullanıcı, fare hareketleriyle bir raketi kontrol ederek, ekranda sürekli hareket eden bir topu yere düşürmeden havada tutmaya ve puan kazanmaya çalışır.

🌟 Özellikler
Akıcı Oyun Döngüsü: QTimer kullanılarak saniyede 50 kare (FPS) hızında çalışan akıcı bir fizik motoruna sahiptir.

Fare ile Kontrol (Mouse Tracking): Raket (buton), fare imlecinin yatay hareketlerini anlık olarak takip eder. Tıklamaya gerek kalmadan sürükleme mantığı ile çalışır.

Çarpışma Algılama (Collision Detection): Topun pencere kenarlarına ve rakete çarpması matematiksel olarak hesaplanır (intersects metodu) ve top fizik kurallarına uygun olarak seker.

Skor Sistemi: Top rakete her çarptığında oyuncu puan kazanır ve skor anlık olarak raketin üzerinde güncellenir.

Oyun Sonu Efekti: Eğer top raketi ıskalar ve yere düşerse oyun durur ve özel bir "patlama" efekti görüntülenir.

Nesne Yönelimli Tasarım (OOP): Top nesnesi, QLabel sınıfından miras alınarak özelleştirilmiş bir Top sınıfı olarak tasarlanmıştır.

🛠️ Kullanılan Teknolojiler
Dil: C++ (C++17 Standartları)

Framework: Qt 6 (Widgets Modülü)

IDE: Qt Creator

Yapı Sistemi: qmake

Temel Sınıflar: QMainWindow, QTimer, QMouseEvent, QPushButton, QLabel

📂 Proje Yapısı
mainwindow.cpp: Oyunun beyni. Fizik hesaplamaları, zamanlayıcı ve fare kontrolleri burada yönetilir.

top.cpp: Top nesnesinin görsel özelliklerini belirleyen sınıf.

resimler.qrc: Oyun içindeki görselleri (top ve patlama efekti) proje içine gömen kaynak dosyası.

🚀 Kurulum ve Çalıştırma
Bu projeyi bilgisayarınıza indirin (Clone veya Download ZIP).

SekenTop.pro dosyasını Qt Creator ile açın.

Projeyi derleyin (Ctrl+B) ve çalıştırın (Ctrl+R).

Oyun başladığında fareyi sağa sola hareket ettirerek topu yakalamaya çalışın!

Geliştirici: Muhammed Mustafa Uysal
