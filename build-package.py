#!/usr/bin/python3
""" This file is part of Automatic Isolated User Sandbox builder

    Debian Sandbox Builder is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Frankenftp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Frankenftp.  If not, see <https://www.gnu.org/licenses/>.
"""

import os
import pathlib
import sys
import argparse
parse = argparse.ArgumentParser(prog="Automatic Isolated User Sandbox builder",
epilog="Copyright (C) le0nklcpp,2024\
    This program is free software: you can redistribute it and/or modify\n\
    it under the terms of the GNU General Public License as published by\n\
    the Free Software Foundation, either version 3 of the License, or\n\
    (at your option) any later version")
cwd = '.'
templatedict = {
'%USER%':None,
'%PKGNAME%':None,
'%MAINTAINER%':None,
'%MAINTAINER_EMAIL%':None,
'%PROVIDES%':None,
'%SECTION%':None,
'%HOMEPAGE%':None,
'%PKDOMAIN%':None,
'%APP_EXE%':None,
'%VENDOR%':'le0nklcpp',
'%DESKTOPNAME%':None,
'%ICON%':None,
'%EXTRA_DEPS%':'',
'%DESKTOP_CAT%':'Network'
}
renamefiles = {
'/usr/share/polkit-1/actions/app.domain.container.actions':'%PKDOMAIN%.actions',
'/usr/share/applications/desktop/app-container.desktop':'%PKGNAME%.desktop',
'/usr/bin/app-container':'%USER%-container',
'/usr/bin/run-app-container':'run-%USER%-container',
'/var/lib/polkit-1/localauthority/50-local.d/10-passwordless-app-container.pkla':'10-passwordless-%PKGNAME%-container.pkla'
}
argnames = {
'--name':'%PKGNAME%',
'--user':'%USER%',
'--maintainer':'%MAINTAINER%',
'--maintainer-email':'%MAINTAINER_EMAIL%',
'--provides':'%PROVIDES%',
'--section':'%SECTION%',
'--homepage':'%HOMEPAGE%',
'--pkdomain':'%PKDOMAIN%',
'--exe':'%APP_EXE%',
'--polkit-vendor':'%VENDOR%',
'--desktop-name':'%DESKTOPNAME%',
'--icon':'%ICON%',
'--extra-deps':'%EXTRA_DEPS%',
'--desktop-cat':'%DESKTOP_CAT%'
}
def replace_template(fl,root):
    f = open(root+fl.name,'r')
    data = f.read()
    f.close()
    for d in templatedict:
     data = data.replace(d,templatedict[d])
    newroot = root.replace('template',templatedict['%PKGNAME%'],1)
    newfile = newroot+fl.name
    for rf in renamefiles:
     if (root+fl.name) == ('template/debian'+rf):
          print("Changing file name for "+fl.name)
          newfile = newroot+renamefiles[rf]
    nf = open(newfile,"w")
    nf.write(data)
    nf.close()
def rec_apply(d,root):
    for fl in d.iterdir():
     if fl.is_dir():
          newpath = root.replace('template',templatedict['%PKGNAME%'],1) + fl.name
          os.mkdir(newpath)
          rec_apply(fl,root+fl.name+'/')
     else:
          replace_template(fl,root)
def read_args():
    for args in argnames:
     parse.add_argument(args,required=(templatedict[argnames[args]]==None))
    args = vars(parse.parse_args())
    for i in args:
     arg = '--'+i
     arg = arg.replace('_','-') # What a bright idea to fix what is not broken
     if(arg in argnames)and(args[i]!=None):
      templatedict[argnames[arg]] = args[i]

def main_action():
    cwd = os.getcwd()
    read_args()
    os.mkdir(templatedict['%PKGNAME%'])
    for i in renamefiles:
     for k in templatedict:
      renamefiles[i] = renamefiles[i].replace(k,templatedict[k])
    rec_apply(pathlib.Path('template'),'template/')
    os.system("chmod 755 -R "+templatedict['%PKGNAME%'])
    os.system("dpkg-deb --build --root-owner-group "+templatedict['%PKGNAME%']+'/debian')
    print("[Done]Thank you for using this tool :3")
if __name__=="__main__":
 main_action()