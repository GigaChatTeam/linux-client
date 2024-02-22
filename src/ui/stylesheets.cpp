/* ----------------------------------------------------------------------------
   gigachat-linux-client - A linux client for gigachat digital ecosystem
   Copyright (C) 2024 Sotov Konstantin A

   This file is part of linux client for gigachat.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 3 of
   the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.
   ----------------------------------------------------------------------------
*/

#include "ui/stylesheets.hpp"

namespace StyleSheets
{

/*const*/ QString SVGBGSS = /*Scalable Vector Graphics BackGround Style Sheet*/
    "background-color: transparent;"
    "font-family: 'Comic Sans MS';"
    "border: 4px solid white;"
    "border-radius: 5px;"
    "color: white;"
    "font-size: 24pt;";

/*const*/ QString FailedAuthSS =
    "NoNewLineQLineEdit {"
    "border: 4px solid red;"
    "border-radius: 2px;"
    "background-color: #f0f0f0;}";

/*const*/ QString LabelSS =
    "color: white;"
    "font: bold 24pt \"Comic Sans MS\";";

/*const*/ QString CheckboxSS =
    "color: white;"
    "font: bold 20 pt;"
    "alignment: center";

#ifdef QT_DEBUG
/*const*/ QString MessageDBGSS =
    "color: yellow;"
    "border: 3px solid yellow;"
    "border-radius: 10px;"
    "background-color: black;";
#endif

/*const*/ QString MessageSS =
    "color: yellow;"
    "background-color: black;"
    "border: 3px solid black;"
    "border-radius: 4px;";

/*const*/ QString MessageSenderSS =
    "color: #1f1e33;"
    "border: 1px solid black;"
    "border-radius: 4px;"
    "background-color: white";

/*const*/ QString MessageErrorSS =
    "color: #505050;"
    "border: 3px solid gray;"
    "font: bold;";

} // namespace StyleSheets
