/*
Copyright 2012, 2013
Author Nicolas Edh,
Nicolas.Edh@gmail.com,
or user "nsf" at cfd-online.com

This file is part of hexBlocker.

    hexBlocker is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    hexBlocker is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with hexBlocker.  If not, see <http://www.gnu.org/licenses/>.

    The license is included in the file COPYING.
*/

#ifndef HEXBC_H
#define HEXBC_H

#include <vtkSmartPointer.h>
#include <vtkObject.h>
#include <iostream>
#include <QTextStream>


//Pre declarations
class vtkIdList;
class vtkCollection;
class hexPatch;



class HexBC : public vtkObject
{
vtkTypeMacro(HexBC,vtkObject)

protected:
    HexBC();
    ~HexBC();
    HexBC(const HexBC&);  // Not implemented in order to comply with vtkObject.
    void operator=(const HexBC&);  // Not implemented in order to comply with vtkObject.

public:
    static HexBC *New();
    // inorder to comply with vtkObect
    void PrintSelf(ostream &os, vtkIndent indent);

    vtkSmartPointer<vtkIdList> patchIds;
    vtkSmartPointer<vtkCollection> globalPatches;
    void setPatchColors(double r,double g, double b);
    void resetPatchColors();

    //Removes patch and reduces ids a
    void notifyRemovedPatch(hexPatch *p);

    //Removes patch from list
    void removePatchFromList(hexPatch *p);
    // finds id of patch in global list returns true if it was found
    bool insertPatchIfIdsExists(vtkSmartPointer<vtkIdList> ids);
    std::string name;
    std::string type;
private:


};

#endif // HEXBLOCK_H
