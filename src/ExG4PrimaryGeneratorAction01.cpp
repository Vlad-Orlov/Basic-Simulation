
/// \file ExG4PrimaryGeneratorAction01.cpp
/// \brief Implementation of the ExG4PrimaryGeneratorAction01 class

#include "ExG4PrimaryGeneratorAction01.hh"
// Подключаем необходимы заголовочные файлы
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

// Класс, в котором описывается положение, тип, энергия, направление вылета
// и распределение начальных частиц
ExG4PrimaryGeneratorAction01::ExG4PrimaryGeneratorAction01()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0), 
  fEnvelopeBox(0)
{
  // По умолчанию поставим 1 частицу
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // Получаем встроеную в Geant4 таблицу частиц
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  // Ищем частицу, в нашем случае протон
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  // Устанавливаем полученную частицу в качестве испускаемого типа начальных частиц в источнике
  fParticleGun->SetParticleDefinition(particle);
  // Устанавливаем направление движение частицы по (x,y,z)
  // Здесь устанавливается направление вдоль оси Z
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  // Установка начальной энергии испускаемых частиц, 2.8 МэВ
  fParticleGun->SetParticleEnergy(2.8*MeV);
}

// Деструктор
ExG4PrimaryGeneratorAction01::~ExG4PrimaryGeneratorAction01()
{
  // удаляем созданный в конструкторе экземпляр класса источника G4ParticleGun
  delete fParticleGun;
}

void ExG4PrimaryGeneratorAction01::GeneratePrimaries(G4Event* anEvent)
{
  //Эта функция вызывается в начале каждого первичного события запуска частицы
  // Для избежания зависимости этого класса от класса DetectorConstruction,
  // мы получаем ссылку на объем детектора через класс G4LogicalVolumeStore
  
  G4double envSizeXY = 0;
  G4double envSizeZ = 0;
  // Проверяем или ссылка на fEnvelopeBox пустая
  if (!fEnvelopeBox)
  {
     // Если пустая, то получаем ссылку на объем детектора
    G4LogicalVolume* envLV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("Detector");
    if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  }
  // Получаем размеры объема, стороны по x и y предполагается что одинаковы
  if ( fEnvelopeBox ) {
    envSizeXY = fEnvelopeBox->GetXHalfLength()*2.;
    envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
  }  
  else  {//Если ссылка на fEnvelopeBox пустая, выдаем предупреждение
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n"; 
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("B1PrimaryGeneratorAction::GeneratePrimaries()",
     "MyCode0002",JustWarning,msg);
  }
  // Объявляем переменные положения пушки частиц
  G4double x0 = 0;
  G4double y0 = 0;
  G4double z0 = -0.5 * 20*cm;
  // Устанавливаем положение
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  // Генерируем первичное событие
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
