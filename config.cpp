class CfgPatches
{
  class BedRespawningRaG
  {
    units[]={};
    weapons[]={};
    requiredVersion=0.1;
    requiredAddons[]={
      "DZ_Data",
      "DZ_Scripts",
      "BedRespawning",
      "rag_baseitems"
    };
  };
};

class CfgMods
{
  class BedRespawningRaG
  {
    dir="BedRespawning-RaG";
    picture="";
    action="";
    hideName=0;
    hidePicture=1;
    name="BedRespawningRaG";
    credits="Mka0207,Tyson";
    author="moldypenguins";
    authorID="76561198312711389";
    version="1.0";
    type="mod";
    dependencies[]={
      "World"
    };
    class defs
    {
      class worldScriptModule
      {
        value="";
        files[]={
          "BedRespawning-RaG/scripts/4_World"
        };
      };
    };
  };
};
