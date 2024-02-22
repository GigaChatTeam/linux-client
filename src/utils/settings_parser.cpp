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

#include "utils/settings_parser.hpp"
#include "utils/properties.hpp"
#include <algorithm>
#include <qtenvironmentvariables.h>

bool alphanumeric(char c)
{
	return ('a' < c && c < 'z') || ('A' < c && c < 'Z') || ('0' < c && c < '9') || c == '_' || c == '-';
}

/// replaces all environmental variables in std::string with their values IF the variable is not empty
/// to escape replacing you can add write \$
/// variable names follow regex "[a-zA-Z0-9_-]" (alphanumeric + underscore and dash)
QString parse_env_string(const std::string &str)
{
	QString	      ret	= QString::fromStdString(str);
	QSet<QString> variables = {};
	for (qsizetype i = 0; i < ret.size(); ++i) {
		if (ret[i] == '$') {
			if (i > 0 and ret[i - 1] == '\\') continue;
			qsizetype vname_start = i + 1;			    // dollar sign location
			while (alphanumeric(str[++i]) && i < ret.size()) {} // first whitespace
			variables.insert(ret.sliced(vname_start, i - vname_start));
		}
	}
	for (auto x : variables) {
		QString env = qgetenv(x.toLocal8Bit().constData());
		ret.replace("\\$", "$\\");
		if (env.size() != 0) ret.replace('$' + x, env);
		ret.replace("$\\", "$");
	}
	return ret;
}

void init_config(const char *path) { config.readFile(path); }

bool init_paths()
{
	std::string db;
	std::string cacheFolder;
	if (!config.lookupValue("paths.database", db) || !config.lookupValue("paths.cache", cacheFolder)) {
		FILEPATHS.dbName      = parse_env_string("$HOME/.local/share/gigachat/gigachat.db");
		FILEPATHS.cacheFolder = parse_env_string("$HOME/.");
		return false;
	}
	FILEPATHS.dbName      = parse_env_string(db);
	FILEPATHS.cacheFolder = parse_env_string(cacheFolder);
	return true;
}

bool init_servers()
{
	std::string ac, dlb, rtcd, rtcda, cloud;
	if (!config.lookupValue("servers.AC", ac) || !config.lookupValue("servers.DLB", dlb) ||
	    !config.lookupValue("servers.RTCD", rtcd) || !config.lookupValue("servrs.RTCDAUTH", rtcda) ||
	    !config.lookupValue("servers.CLOUD", cloud)) {
		SERVERS.rtcdServer  = "ws://10.242.40.127:8080";
		SERVERS.rtcdAuth    = "http://10.242.40.127:8081";
		SERVERS.loginServer = "http://10.242.40.127:8082";
		SERVERS.dlbServer   = "http://10.242.40.127:8084";
		SERVERS.cloud	    = "https://10.242.40.127:9005";
		return false;
	}
	SERVERS.loginServer = parse_env_string(ac);
	SERVERS.rtcdServer  = parse_env_string(rtcd);
	SERVERS.dlbServer   = parse_env_string(dlb);
	SERVERS.rtcdAuth    = parse_env_string(rtcda);
	SERVERS.cloud	    = parse_env_string(cloud);
	return true;
}
