/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011-2016 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "structuredFaceAreaPairGAMGAgglomeration.H"
#include "fvMesh.H"
#include "surfaceFields.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(structuredFaceAreaPairGAMGAgglomeration, 0);
    bool structuredFaceAreaPairGAMGAgglomeration::forward_(true);

    addToRunTimeSelectionTable
    (
        GAMGAgglomeration,
        structuredFaceAreaPairGAMGAgglomeration,
        lduMesh
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::structuredFaceAreaPairGAMGAgglomeration::
structuredFaceAreaPairGAMGAgglomeration
(
    const lduMesh& mesh,
    const dictionary& controlDict
)
:
    GAMGAgglomeration(mesh, controlDict),
    mergeLevels_(controlDict.lookupOrDefault<label>("mergeLevels", 1))
{
    const fvMesh& fvmesh = refCast<const fvMesh>(mesh);

    //agglomerate(mesh, sqrt(fvmesh.magSf().primitiveField()));
    agglomerate
    (
        mesh,
        mag
        (
            cmptMultiply
            (
                fvmesh.Sf().primitiveField()
               /sqrt(fvmesh.magSf().primitiveField()),
                vector(1, 1.01, 1.02)
                //vector::one
            )
        )
    );
}


// ************************************************************************* //
