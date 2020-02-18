/// \file ExG4DetectorConstruction01.cpp
/// \brief Implementation of the ExG4DetectorConstruction01 class

#include "ExG4DetectorConstruction01.hh"
#include "ExG4DetectorSD.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

// Конструктор класса объявления материалов и геометрии всей моделируемой системы
ExG4DetectorConstruction01::ExG4DetectorConstruction01()
: G4VUserDetectorConstruction()
{ }

// Деструктор
ExG4DetectorConstruction01::~ExG4DetectorConstruction01()
{ }

// Функция определения материалов и геометрии всей системы,
// должна возвращать физический объем - ссылку на экземпляр класса G4VPhysicalVolume
// Геометрию проектировать будем следующую: пучок протонов попадает на мишень
// вольфрамовый лист толщиной около 1 мм, а за мишень поставим детектор
// таких же размеров, он будет регистрировать что в него попало.
G4VPhysicalVolume* ExG4DetectorConstruction01::Construct()
{  
    // Для простоты используем предопределенные в Geant4 материалы
    // Так объявляется менеджер, из которого можно извлечь
    // ранее предопределенные материалы
  G4NistManager* nist = G4NistManager::Instance();

  // Параметры детектора
  G4double det_sizeXY = 25*cm, det_sizeZ = 0.15*cm;

  // Материал детектора, здесь выбираем вольфрам
  G4Material* det_mat = nist->FindOrBuildMaterial("G4_W");
   
  // Опция для включения/выключения проверки перекрытия объемов
  G4bool checkOverlaps = true;

  // World
  // Объем мира, самый большой объем, включающий остальные, аналог экспериментального
  // зала
  G4double world_sizeXY = 30*cm;//Размер по x и y здесь будут одинаковы - ширина и высота
  G4double world_sizeZ  = 20*cm;//Размер по z - толщина
  // Выбор материала для мира из предопределенных в Geant4, для зала берем воздух
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  // Создание объема для мира (экспериментального зала), определяется сама форма объема,
  // берем параллелепипед, это просто геометрическая фигура
  G4Box* solidWorld =
  new G4Box("World",                       //its name, название объема
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size, его размеры
  // указываются половины размеров высоты, ширины и глубины

  // Логический объем, здесь подключается материал, из которого сделан объем
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid, геометрический объем, объявлен выше
                        world_mat,           //its material, материал объема
                        "World");            //its name, название логического объема
  //совпадает с названием объема, но
  //для Geant4 это разные объекты
  //геометрический объем и логический объем

  //Физический объем, а теперь наш логический объем помещаем в "реальный" мир
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation, нет вращения
                      G4ThreeVector(),       //at (0,0,0), расположение в центре (0,0,0)
                      logicWorld,            //its logical volume, логический объем этого физического
                      "World",               //its name, название физического объема
                      0,                     //its mother  volume, материнский объем, этот самый первый, поэтому 0
                      false,                 //no boolean operation, без логических (булевых) операций
                      0,                     //copy number, номер копии
                      checkOverlaps);        //overlaps checking, флаг проверки перекрытия объемов
                        
  // Детектор, для него также используем параллелепипед
  G4Box* solidDet =
    new G4Box("Detector",                    //its name, имя
        0.5*det_sizeXY, 0.5*det_sizeXY, 0.5*det_sizeZ); //its size, размеры

  //Логический объем
  G4LogicalVolume* logicDet =
    new G4LogicalVolume(solidDet,            //its solid, объем
                        det_mat,             //its material, указываем материал детектора
                        "Detector");         //its name, его имя

  //Физический объем детектора
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,5*cm), //at (0,0,5 см) положение центра детектора, он смещен на 5 см от центра объема World
                    logicDet,                //its logical volume, подключаем логический объем
                    "Detector",              //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем, помещаем в world!
                    false,                   //no boolean operation, без булевых операций
                    0,                       //copy number, номер копии
                    checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов

  // Для мишени, на которую будет падать пучек, возьмем геометрические размеры как
  // у детектора, параллелепипед - лист вольфрама.
  //Логический объем
  G4LogicalVolume* logicTar =
    new G4LogicalVolume(solidDet,            //its solid, объем
                        det_mat,             //its material, указываем материал мишени
                        "Target");         //its name, его имя

  //Физический объем мишени
  new G4PVPlacement(0,                       //no rotation, так же без вращения
                    G4ThreeVector(0,0,-5*cm),//at (0,0,-5 см) положение центра мишени в другую сторону от детектора, смещена на 5 см от центра объема World
                    logicTar,                //its logical volume, подключаем логический объем
                    "Target",                //its name, имя физического объема
                    logicWorld,              //its mother  volume, родительский логический объем!
                    false,                   //no boolean operation, без булевых операций
                    0,                       //copy number, номер копии
                    checkOverlaps);
  //Всегда возвращает физический объем
  return physWorld;
}

void ExG4DetectorConstruction01::ConstructSDandField()
{
  // Объявление чувствительной области детектора, в которой можно получить подробную
  // информацию о состоянии и движении частицы
  // Назовем чувствительную область DetectorSD
  G4String trackerChamberSDname = "DetectorSD";
  // Создаем экземпляр чувствительной области
  ExG4DetectorSD* aTrackerSD = new ExG4DetectorSD(trackerChamberSDname);
  // Передаем указатель менеджеру
  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  // Добавляем чувствительный объем ко всем логическим областям с
  // именем Detector
  SetSensitiveDetector("Detector", aTrackerSD, true);
}
