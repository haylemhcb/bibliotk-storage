import sys
import os
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtWebEngineWidgets import QWebEngineView
from PyQt5.QtCore import QUrl 

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        # Configurar el tamaño de la ventana
        self.setWindowTitle("Bibliotk")
        self.setGeometry(100, 100, 640, 480)

        # Crear un QWebEngineView
        self.browser = QWebEngineView()

        # Cargar la página local index.html desde la carpeta actual
        current_dir = os.path.dirname(os.path.abspath(__file__))  # Obtener el directorio actual
        self.browser.setUrl(QUrl("http://localhost:4798"))

        # Establecer el QWebEngineView como el widget central
        self.setCentralWidget(self.browser)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
