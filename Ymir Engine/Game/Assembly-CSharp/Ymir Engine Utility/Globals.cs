using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace YmirEngine
{
    public static class Globals
    {
        public static string saveGameDir = "Assets/GameFiles/";
        public static string saveGameExt = ".ygame";

        public static string saveGamesInfoFile = "Game Files";
        public static string saveCurrentGame = "CurrentGameFile";

        public static Player GetPlayerScript()
        {
            GameObject gameObject = InternalCalls.GetGameObjectByName("Player");

            if (gameObject != null)
            {
                return gameObject.GetComponent<Player>();
            }

            return null;
        }
        public static Health GetPlayerHealthScript()
        {
            GameObject gameObject = InternalCalls.GetGameObjectByName("Player");

            if (gameObject != null)
            {
                return gameObject.GetComponent<Health>();
            }

            return null;
        }

        #region DEFINE ITEMS

        // Items dictionary
        public static Dictionary<string, Item> itemsDictionary = new Dictionary<string, Item>();

        public static void CreateItemDictionary()
        {
            itemsDictionary.Add("skin_common", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.COMMON,
                /*isEquipped*/      false,
                /*name*/            "Alien Skin",
                /*description*/     "\nIt's made of a tough\nmaterial, capable of\nresisting the\ncreatures own acid\n\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/SkinIconColor.png",
                /*dictionaryName*/  "skin_common"
                    ));

            itemsDictionary.Add("skin_rare", new
               Item(
               /*always none*/     ITEM_SLOT.NONE,
               /*item type*/       ITEM_SLOT.MATERIAL,
               /*itemRarity*/      ITEM_RARITY.RARE,
               /*isEquipped*/      false,
               /*name*/            "Alien Skin",
                /*description*/     "\nIt's made of a tough\nmaterial, capable of\nresisting the\ncreatures own acid\n\n\n-Material-",
               /*imagePath*/       "Assets/UI/Items Slots/Iconos/SkinIconColor.png",
               /*dictionaryName*/  "skin_rare"
                   ));

            itemsDictionary.Add("skin_epic", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.EPIC,
                /*isEquipped*/      false,
                /*name*/            "Alien Skin",
                /*description*/     "\nIt's made of a tough\nmaterial, capable of\nresisting the\ncreatures own acid\n\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/SkinIconColor.png",
                /*dictionaryName*/  "skin_epic"
                    ));

            itemsDictionary.Add("claw_common", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.COMMON,
                /*isEquipped*/      false,
                /*name*/            "Alien Claw",
                /*description*/     "\nExtremely sharp claw,\ncapable of slicing\nthrough almost\nanything within its\ngrasp\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/ClawIconColor.png",
                /*dictionaryName*/  "claw_common"
                    ));

            itemsDictionary.Add("claw_rare", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.RARE,
                /*isEquipped*/      false,
                /*name*/            "Alien Claw",
                /*description*/     "\nExtremely sharp claw,\ncapable of slicing\nthrough almost\nanything within its\ngrasp\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/ClawIconColor.png",
                /*dictionaryName*/  "claw_rare"
                    ));

            itemsDictionary.Add("claw_epic", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.EPIC,
                /*isEquipped*/      false,
                /*name*/            "Alien Claw",
                /*description*/     "\nExtremely sharp claw,\ncapable of slicing\nthrough almost\nanything within its\ngrasp\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/ClawIconColor.png",
                /*dictionaryName*/  "claw_epic"
                    ));

            itemsDictionary.Add("tailtip_common", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.COMMON,
                /*isEquipped*/      false,
                /*name*/            "Alien Tail Tip",
                /*description*/     "\nA sharp metallic piece\nof the tail, they use\nit as a slicing weapon\n\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/TailIconColor.png",
                /*dictionaryName*/  "tailtip_common"
                    ));

            itemsDictionary.Add("tailtip_rare", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.RARE,
                /*isEquipped*/      false,
                /*name*/            "Alien Tail Tip",
                /*description*/     "\nA sharp metallic piece\nof the tail, they use\nit as a slicing weapon\n\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/TailIconColor.png",
                /*dictionaryName*/  "tailtip_rare"
                    ));

            itemsDictionary.Add("tailtip_epic", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.EPIC,
                /*isEquipped*/      false,
                /*name*/            "Alien Tail Tip",
                /*description*/     "\nA sharp metallic piece\nof the tail, they use\nit as a slicing weapon\n\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/TailIconColor.png",
                /*dictionaryName*/  "tailtip_epic"
                    ));

            itemsDictionary.Add("acidvesicle_common", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.COMMON,
                /*isEquipped*/      false,
                /*name*/            "Alien Acid Vesicle",
                /*description*/     "\nAcid-filled organic\nbags, can be useful\nfor some crafts\n\n\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/AcidVesicleIconColor.png",
                /*dictionaryName*/  "acidvesicle_common"
                    ));

            itemsDictionary.Add("acidvesicle_rare", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.RARE,
                /*isEquipped*/      false,
                /*name*/            "Alien Acid Vesicle",
                /*description*/     "\nAcid-filled organic\nbags, can be useful\nfor some crafts\n\n\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/AcidVesicleIconColor.png",
                /*dictionaryName*/  "acidvesicle_rare"
                    ));

            itemsDictionary.Add("acidvesicle_epic", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.EPIC,
                /*isEquipped*/      false,
                /*name*/            "Alien Acid Vesicle",
                /*description*/     "\nAcid-filled organic\nbags, can be useful\nfor some crafts\n\n\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/AcidVesicleIconColor.png",
                /*dictionaryName*/  "acidvesicle_epic"
                    ));

            itemsDictionary.Add("exocranium_common", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.COMMON,
                /*isEquipped*/      false,
                /*name*/            "Alien Exocranium",
                /*description*/     "\nAn elongated shell.\nHard, resistant and\nlight. Sometimes\ncontaining some\nvesicles on the sides\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/ExocraniumIconColor.png",
                /*dictionaryName*/  "exocranium_common"
                    ));

            itemsDictionary.Add("exocranium_rare", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.RARE,
                /*isEquipped*/      false,
                /*name*/            "Alien Exocranium",
                /*description*/     "\nAn elongated shell.\nHard, resistant and\nlight. Sometimes\ncontaining some\nvesicles on the sides\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/ExocraniumIconColor.png",
                /*dictionaryName*/  "exocranium_rare"
                    ));

            itemsDictionary.Add("exocranium_epic", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.EPIC,
                /*isEquipped*/      false,
                /*name*/            "Alien Exocranium",
                /*description*/     "\nAn elongated shell.\nHard, resistant and\nlight. Sometimes\ncontaining some\nvesicles on the sides\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/ExocraniumIconColor.png",
                /*dictionaryName*/  "exocranium_epic"
                    ));

            itemsDictionary.Add("bone_common", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.COMMON,
                /*isEquipped*/      false,
                /*name*/            "Alien Aluminium Bone",
                /*description*/     "\nIt is light, soft,\nmalleable, and a good\nconductor of both\nelectricity and heat\n\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/BoneIconColor.png",
                /*dictionaryName*/  "bone_common"
                    ));

            itemsDictionary.Add("bone_rare", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.RARE,
                /*isEquipped*/      false,
                /*name*/            "Alien Aluminium Bone",
                /*description*/     "\nIt is light, soft,\nmalleable, and a good\nconductor of both\nelectricity and heat\n\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/BoneIconColor.png",
                /*dictionaryName*/  "bone_rare"

                    ));

            itemsDictionary.Add("bone_epic", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.EPIC,
                /*isEquipped*/      false,
                /*name*/            "Alien Aluminium Bone",
                /*description*/     "\nIt is light, soft,\nmalleable, and a good\nconductor of both\nelectricity and heat\n\n\n-Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/BoneIconColor.png",
                /*dictionaryName*/  "bone_epic"
                    ));

            itemsDictionary.Add("core_mythic", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.MYTHIC,
                /*isEquipped*/      false,
                /*name*/            "Mythical Alien Core",
                /*description*/     "\nAn amazing but\nunknown part of the\nalien, it can be used to\nupgrade your weapon\n\n\n-Upgrade Material-",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/AlienCoreIconColor.png",
                /*dictionaryName*/  "core_mythic"
                    ));

            itemsDictionary.Add("upgradevessel_mythic", new
                Item(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.MATERIAL,
                /*itemRarity*/      ITEM_RARITY.MYTHIC,
                /*isEquipped*/      false,
                /*name*/            "Resin Vessel",
                /*description*/     "\nAdds permanently\none more Resin Vessel\nwhen crafted, allowing\nyou to get more heals\non the raid\n\n+1 Ressin Vessel",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/ResinVesselIconColor.png",
                /*dictionaryName*/  "upgradevessel_mythic"
                    ));

            // Item Name: 
            itemsDictionary.Add("armor_common", new
                I_Equippable(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.ARMOR,
                /*itemRarity*/      ITEM_RARITY.COMMON,
                /*isEquipped*/      false,
                /*name*/            "Exo-Armor",
                /*description*/     "\nAn exo-armor that will\nhelp you withstand the\nblows of Xenomorphs.\nIt's light and tough.\n\n             +10 Armor",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/ArmorIconColor.png",
                /*dictionaryName*/  "armor_common",
                /*HP*/                  0,
                /*armor*/               10,
                /*speed*/               0,
                /*fireRate*/            0,
                /*reloadSpeed*/         0,
                /*damageMultiplier*/    0
                ));

            itemsDictionary.Add("armor_rare", new
                I_Equippable(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.ARMOR,
                /*itemRarity*/      ITEM_RARITY.RARE,
                /*isEquipped*/      false,
                /*name*/            "Exo-Armor",
                /*description*/     "\nAn exo-armor that will\nhelp you withstand the\nblows of Xenomorphs.\nIt's light and tough.\n\n             +18 Armor",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/ArmorIconColor.png",
                /*dictionaryName*/  "armor_rare",
                /*HP*/                  0,
                /*armor*/               18,
                /*speed*/               0,
                /*fireRate*/            0,
                /*reloadSpeed*/         0,
                /*damageMultiplier*/    0
                ));

            itemsDictionary.Add("armor_epic", new
                I_Equippable(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.ARMOR,
                /*itemRarity*/      ITEM_RARITY.EPIC,
                /*isEquipped*/      false,
                /*name*/            "Exo-Armor",
                /*description*/     "\nAn exo-armor that will\nhelp you withstand the\nblows of Xenomorphs.\nIt's light and tough.\n\n             +25 Armor",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/ArmorIconColor.png",
                /*dictionaryName*/  "armor_epic",
                /*HP*/                  0,
                /*armor*/               25,
                /*speed*/               0,
                /*fireRate*/            0,
                /*reloadSpeed*/         0,
                /*damageMultiplier*/    0
                ));

            itemsDictionary.Add("ofChip_common", new
                I_Equippable(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.CHIP,
                /*itemRarity*/      ITEM_RARITY.COMMON,
                /*isEquipped*/      false,
                /*name*/            "Offensive Chip",
                /*description*/     "\nA thin layer made of\naluminum with cables.\nBoosts the offensive\ncapabilities.\n            +10% Speed\n        +5% Reload spd.\n         +12.5% Damage",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/OffensiveChipIcon2Color.png",
                /*dictionaryName*/  "ofChip_common",
                /*HP*/                  0,
                /*armor*/               0,
                /*speed*/               1,
                /*fireRate*/            0,
                /*reloadSpeed*/         5.0f,
                /*damageMultiplier*/    12.5f
                ));

            itemsDictionary.Add("ofChip_rare", new
                I_Equippable(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.CHIP,
                /*itemRarity*/      ITEM_RARITY.RARE,
                /*isEquipped*/      false,
                /*name*/            "Offensive Chip",
                /*description*/     "\nA thin layer made of\naluminum with cables.\nBoosts the offensive\ncapabilities.\n            +20% Speed\n        +9% Reload spd.\n          +24% Damage",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/OffensiveChipIcon2Color.png",
                /*dictionaryName*/  "ofChip_rare",
                /*HP*/                  0,
                /*armor*/               0,
                /*speed*/               2,
                /*fireRate*/            0,
                /*reloadSpeed*/         9.0f,
                /*damageMultiplier*/    24f
                ));

            itemsDictionary.Add("ofChip_epic", new
                I_Equippable(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.CHIP,
                /*itemRarity*/      ITEM_RARITY.EPIC,
                /*isEquipped*/      false,
                /*name*/            "Offensive Chip",
                /*description*/     "\nA thin layer made of\naluminum with cables.\nBoosts the offensive\ncapabilities.\n            +20% Speed\n       +15% Reload spd.\n          +24% Damage",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/OffensiveChipIcon2Color.png",
                /*dictionaryName*/  "ofChip_epic",
                /*HP*/                  0,
                /*armor*/               0,
                /*speed*/               3,
                /*fireRate*/            0,
                /*reloadSpeed*/         15.0f,
                /*damageMultiplier*/    45f
                ));

            itemsDictionary.Add("defChip_common", new
                I_Equippable(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.CHIP,
                /*itemRarity*/      ITEM_RARITY.COMMON,
                /*isEquipped*/      false,
                /*name*/            "Defensive Chip",
                /*description*/     "\nA thick layer made of\naluminum with cables.\nBoosts the defensive\ncapabilities.\n\n              +5 Armor",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/DefensiveChipIcon2Color.png",
                /*dictionaryName*/  "defChip_common",
                /*HP*/                  0,
                /*armor*/               5,
                /*speed*/               0,
                /*fireRate*/            0,
                /*reloadSpeed*/         0,
                /*damageMultiplier*/    0
                ));

            itemsDictionary.Add("defChip_rare", new
                I_Equippable(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.CHIP,
                /*itemRarity*/      ITEM_RARITY.RARE,
                /*isEquipped*/      false,
                /*name*/            "Defensive Chip",
                /*description*/     "\nA thick layer made of\naluminum with cables.\nBoosts the defensive\ncapabilities.\n\n              +9 Armor",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/DefensiveChipIcon2Color.png",
                /*dictionaryName*/  "defChip_rare",
                /*HP*/                  0,
                /*armor*/               9,
                /*speed*/               0,
                /*fireRate*/            0,
                /*reloadSpeed*/         0,
                /*damageMultiplier*/    0
                ));

            itemsDictionary.Add("defChip_epic", new
                I_Equippable(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.CHIP,
                /*itemRarity*/      ITEM_RARITY.EPIC,
                /*isEquipped*/      false,
                /*name*/            "Defensive Chip",
                /*description*/     "\nA thick layer made of\naluminum with cables.\nBoosts the defensive\ncapabilities.\n\n             +12 Armor",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/DefensiveChipIcon2Color.png",
                /*dictionaryName*/  "defChip_epic",
                /*HP*/                  0,
                /*armor*/               12.5f,
                /*speed*/               0,
                /*fireRate*/            0,
                /*reloadSpeed*/         0,
                /*damageMultiplier*/    0
                ));

            // Item Name: 
            itemsDictionary.Add("grenade_common", new
                I_Consumables(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.CONSUMABLE,
                /*itemRarity*/      ITEM_RARITY.COMMON,
                /*isEquipped*/      false,
                /*name*/            "Grenade",
                /*description*/     "\nHigh damage explosive\ngrenade that contains\nSpitter's acid\n\n            Damage: 200\n                 Area: 6",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/GrenadeIcon2Color.png",
                /*dictionaryName*/  "grenade_common",
                /*dmg*/             200,
                /*area*/            6,
                /*time*/            0
                ));

            itemsDictionary.Add("grenade_rare", new
                I_Consumables(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.CONSUMABLE,
                /*itemRarity*/      ITEM_RARITY.RARE,
                /*isEquipped*/      false,
                /*name*/            "Grenade",
                /*description*/     "\nHigh damage explosive\ngrenade that contains\nSpitter's acid\n\n            Damage: 360\n                 Area: 7",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/GrenadeIcon2Color.png",
                /*dictionaryName*/  "grenade_rare",
                /*dmg*/             360,
                /*area*/            7,
                /*time*/            0
                ));

            itemsDictionary.Add("grenade_epic", new
                I_Consumables(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.CONSUMABLE,
                /*itemRarity*/      ITEM_RARITY.EPIC,
                /*isEquipped*/      false,
                /*name*/            "Grenade",
                /*description*/     "\nHigh damage explosive\ngrenade that contains\nSpitter's acid\n\n            Damage: 450\n                 Area: 8",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/GrenadeIcon2Color.png",
                /*dictionaryName*/  "grenade_epic",
                /*dmg*/             450,
                /*area*/            8,
                /*time*/            0
                ));

            itemsDictionary.Add("bakerhouse_common", new
                I_Consumables(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.CONSUMABLE,
                /*itemRarity*/      ITEM_RARITY.COMMON,
                /*isEquipped*/      false,
                /*name*/            "Baker House",
                /*description*/     "\nMiniature of a\nlegendary baker house.\nIt attracts enemies\nwith a noise.\n\n               Time: 3s\n               Area: 10",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/BakerHouseIconColor.png",
                /*dictionaryName*/  "bakerhouse_common",
                /*dmg*/             0,
                /*area*/            10,
                /*time*/            3
                ));

            itemsDictionary.Add("bakerhouse_rare", new
                I_Consumables(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.CONSUMABLE,
                /*itemRarity*/      ITEM_RARITY.RARE,
                /*isEquipped*/      false,
                /*name*/            "Baker House",
                /*description*/     "\nMiniature of a\nlegendary baker house.\nIt attracts enemies\nwith a noise.\n\n               Time: 4s\n               Area: 12",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/BakerHouseIconColor.png",
                /*dictionaryName*/  "bakerhouse_rare",
                /*dmg*/             0,
                /*area*/            12,
                /*time*/            4
                ));

            itemsDictionary.Add("bakerhouse_epic", new
                I_Consumables(
                /*always none*/     ITEM_SLOT.NONE,
                /*item type*/       ITEM_SLOT.CONSUMABLE,
                /*itemRarity*/      ITEM_RARITY.EPIC,
                /*isEquipped*/      false,
                /*name*/            "Baker House",
                /*description*/     "\nMiniature of a\nlegendary baker house.\nIt attracts enemies\nwith a noise.\n\n               Time: 6s\n               Area: 15",
                /*imagePath*/       "Assets/UI/Items Slots/Iconos/BakerHouseIconColor.png",
                /*dictionaryName*/  "bakerhouse_epic",
                /*dmg*/             0,
                /*area*/            15,
                /*time*/            6
                ));
        }

        public static Item SearchItemInDictionary(string name)
        {
            string[] parts = name.Split(' ');

            string itemName = parts[0];

            Item _item = itemsDictionary[itemName];

            if (_item.itemType == ITEM_SLOT.ARMOR || _item.itemType == ITEM_SLOT.CHIP)
            {
                return new I_Equippable((I_Equippable)_item);
            }

            else if (_item.itemType == ITEM_SLOT.CONSUMABLE)
            {
                return new I_Consumables((I_Consumables)_item);
            }

            return new Item(_item);
        }
        #endregion
    }
}