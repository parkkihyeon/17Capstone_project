using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Newtonsoft.Json;

static class Constant
{
    public const int WIDTH_SIZE = 10;
    public const int HEIGHT_SIZE = 11;
}

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
    private char[,] Board = new char[Constant.WIDTH_SIZE, Constant.HEIGHT_SIZE];

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
