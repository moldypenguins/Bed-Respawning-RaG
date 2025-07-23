//RaG_BaseItems Compatibility
modded class ActionPackRaGSleepingBag
{
  override void OnFinishProgressServer(ActionData action_data)
  {
    ItemBase item = ItemBase.Cast(action_data.m_Target.GetObject());
    if (GetGame().IsServer() && item && BedFrameWork.IsRaGBed(item.GetType()))
    {
      Print("[Bed-Respawn-RaG] Running OnFinishProgressServer for '" + item.GetType() + "', belonging to: " + item.GetBedOwner());
      if (item.GetBedOwner() != "")
      {
        BedFrameWork.RemoveRespawnData(item.GetBedOwner());
      }
    }
    super.OnFinishProgressServer(action_data);
  }
}

modded class ActionDismantleragbaseitem
{
  override void OnFinishProgressServer(ActionData action_data)
  {
    ItemBase item = ItemBase.Cast(action_data.m_Target.GetObject());
    if (GetGame().IsServer() && item && BedFrameWork.IsRaGBed(item.GetType()))
    {
      Print("[Bed-Respawn-RaG] Running OnFinishProgressServer for '" + item.GetType() + "', belonging to: " + item.GetBedOwner());
      if (item.GetBedOwner() != "")
      {
        BedFrameWork.RemoveRespawnData(item.GetBedOwner());
      }
    }
    super.OnFinishProgressServer(action_data);
  }
}

modded class ItemBase
{
  override void OnPlacementComplete(Man player, vector position = "0 0 0", vector orientation = "0 0 0")
  {
    super.OnPlacementComplete(player, position, orientation);
    if (GetGame().IsServer() && BedFrameWork.IsRaGBedKit(this.GetType()))
    {
      Print("[Bed-Respawn-RaG] OnPlacementComplete - '" + this.GetType() + "'");
      PlayerBase m_Player = PlayerBase.Cast(player);
      string m_PlayerId = m_Player.GetIdentity().GetId();

      float radius = 1.0;
      array<Object> objects = new array<Object>;
      array<CargoBase> cargos = new array<CargoBase>;
      GetGame().GetObjectsAtPosition(position, radius, objects, cargos);
      foreach (Object obj : objects)
      {
        ItemBase item = ItemBase.Cast(obj);
        if (item && BedFrameWork.IsRaGBed(item.GetType()))
        {
          item.SetBedOwner(m_PlayerId);
          item.SetBedUses(BedFrameWork.m_BedConfig.MaxRespawnsBeforeRemoval);
          Print("[Bed-Respawn-RaG] OnPlacementComplete - '" + item.GetType() + "', belonging to: " + item.GetBedOwner());
          BedFrameWork.InsertBed(m_Player, item.GetBedOwner(), position, 0, item.GetBedUses());
          break;
        }
      }
    }
  }

  override void EEDelete(EntityAI parent)
  {
    super.EEDelete(parent);
    if ( this.IsHologram() ) return;
    if (GetGame().IsServer() && BedFrameWork.IsRaGBed(this.GetType()) && this.GetBedOwner() != "")
    {
      Print("[Bed-Respawn-RaG] EEDelete - '" + this.GetType() + "', belonging to: " + this.GetBedOwner());
      BedFrameWork.RemoveRespawnData(this.GetBedOwner());
    }
  }

  override void OnStoreSave(ParamsWriteContext ctx)
  {
    super.OnStoreSave(ctx);
    if (BedFrameWork.IsRaGBed(this.GetType()) && this.GetBedOwner() != "")
    {
      ctx.Write(this.GetBedOwner());
      ctx.Write(this.GetBedUses());
      Print("[Bed-Respawn-RaG] OnStoreSave - '" + this.GetType() + "', belonging to: " + this.GetBedOwner());
    }
  }

  override bool OnStoreLoad(ParamsReadContext ctx, int version)
  {
    if (!super.OnStoreLoad(ctx, version))
      return false;
    if (BedFrameWork.IsRaGBed(this.GetType()))
    {
			if ( !ctx.Read(this.GetBedOwner()) )
				return false;

			if ( !ctx.Read(this.GetBedUses()) )
				return false;

      Print("[Bed-Respawn-RaG] OnStoreLoad - '" + this.GetType() + "', belonging to: " + this.GetBedOwner());
    }
    return true;
  }
}
