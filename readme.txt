generate icon
mkdir resource/app.iconset
iconutil -c icns app.iconset/

make dmg
~/Qt/5.6/clang_64/bin/macdeployqt DynaMon.app -dmg

generate xcode
/usr/local/Cellar/qt
~/Qt/5.6/clang_64/bin/qmake -spec macx-xcode DynaMon.pro

