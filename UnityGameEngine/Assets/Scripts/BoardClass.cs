using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;

[JsonObject(MemberSerialization.OptIn)]
public class _BoardData
{
    [JsonProperty]
    private int Host;

    public int host
    {
        get { return Host; }
        set { Host = value; }
    }

    [JsonProperty]
    private char[,] Board = new char[DefineConstant.WIDTH_SIZE, DefineConstant.HEIGHT_SIZE];

    public char[,] board
    {
        get { return Board; }
        set { Board = value; }
    }

    public string ToJsonString()
    {
        return JsonConvert.SerializeObject(this);
    }
    public _BoardData Deserialize(string jsonString)
    {
        return JsonConvert.DeserializeObject<_BoardData>(jsonString);
    }
}
