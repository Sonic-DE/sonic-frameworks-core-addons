#!/usr/bin/env python3

import sys

from KCoreAddons import KAboutData, KAboutPerson
from PySide6 import QtCore

app = QtCore.QCoreApplication()

about = KAboutData("myapp", "My Application", "1.0")

me = KAboutPerson("Nicolas Fella", "Author", "nicolas.fella@kde.org")
about.addAuthor(me)

KAboutData.setApplicationData(about)

print(f"Hello, this is {about.displayName()} {about.version()}, written by {about.authors()[0].name()}.")

print(f"Hello, from QApp {QtCore.QCoreApplication.applicationName()} {QtCore.QCoreApplication.applicationVersion()}.")

sys.exit(app.exec())
