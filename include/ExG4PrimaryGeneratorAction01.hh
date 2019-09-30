// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes, nor the agencies providing financial support for this*
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// *                                                                  *
// * Разработано специально для dev.asifmoda.com                      *
// * Можно использовать для обучения, частных и коммерческих проектов.*
// * Прывітанне з Беларусі!                                           *
// * Автор, идея и реализация:                                        *
// * Виктор Гавриловец, bycel@tut.by,                                 *
// ********************************************************************
// $Id: ExG4PrimaryGeneratorAction.hh $
//
/// \file ExG4PrimaryGeneratorAction01.hh
/// \brief Definition of the ExG4PrimaryGeneratorAction01 class

#ifndef B1PrimaryGeneratorAction_h
#define B1PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

/// Класс определения источника первичных частиц
class ExG4PrimaryGeneratorAction01 : public G4VUserPrimaryGeneratorAction
{
  public:
    ExG4PrimaryGeneratorAction01();
    virtual ~ExG4PrimaryGeneratorAction01();

    // Метод из базового класса, задает параметры источника начальных частиц
    virtual void GeneratePrimaries(G4Event*);         
  
    // Метод для доступа к источнику частиц (пушке частиц ;) )
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun; // указатель на источник частиц
    // Временная переменная объема
    G4Box* fEnvelopeBox;
};
#endif
