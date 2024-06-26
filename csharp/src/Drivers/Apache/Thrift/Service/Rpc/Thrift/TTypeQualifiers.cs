/**
 * <auto-generated>
 * Autogenerated by Thrift Compiler (0.17.0)
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 * </auto-generated>
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using Thrift;
using Thrift.Collections;
using Thrift.Protocol;
using Thrift.Protocol.Entities;
using Thrift.Protocol.Utilities;
using Thrift.Transport;
using Thrift.Transport.Client;
using Thrift.Transport.Server;
using Thrift.Processor;


#pragma warning disable IDE0079  // remove unnecessary pragmas
#pragma warning disable IDE0017  // object init can be simplified
#pragma warning disable IDE0028  // collection init can be simplified
#pragma warning disable IDE1006  // parts of the code use IDL spelling
#pragma warning disable CA1822   // empty DeepCopy() methods still non-static
#pragma warning disable IDE0083  // pattern matching "that is not SomeType" requires net5.0 but we still support earlier versions

namespace Apache.Hive.Service.Rpc.Thrift
{

  public partial class TTypeQualifiers : TBase
  {

    public Dictionary<string, global::Apache.Hive.Service.Rpc.Thrift.TTypeQualifierValue> Qualifiers { get; set; }

    public TTypeQualifiers()
    {
    }

    public TTypeQualifiers(Dictionary<string, global::Apache.Hive.Service.Rpc.Thrift.TTypeQualifierValue> qualifiers) : this()
    {
      this.Qualifiers = qualifiers;
    }

    public TTypeQualifiers DeepCopy()
    {
      var tmp5 = new TTypeQualifiers();
      if ((Qualifiers != null))
      {
        tmp5.Qualifiers = this.Qualifiers.DeepCopy();
      }
      return tmp5;
    }

    public async global::System.Threading.Tasks.Task ReadAsync(TProtocol iprot, CancellationToken cancellationToken)
    {
      iprot.IncrementRecursionDepth();
      try
      {
        bool isset_qualifiers = false;
        TField field;
        await iprot.ReadStructBeginAsync(cancellationToken);
        while (true)
        {
          field = await iprot.ReadFieldBeginAsync(cancellationToken);
          if (field.Type == TType.Stop)
          {
            break;
          }

          switch (field.ID)
          {
            case 1:
              if (field.Type == TType.Map)
              {
                {
                  var _map6 = await iprot.ReadMapBeginAsync(cancellationToken);
                  Qualifiers = new Dictionary<string, global::Apache.Hive.Service.Rpc.Thrift.TTypeQualifierValue>(_map6.Count);
                  for(int _i7 = 0; _i7 < _map6.Count; ++_i7)
                  {
                    string _key8;
                    global::Apache.Hive.Service.Rpc.Thrift.TTypeQualifierValue _val9;
                    _key8 = await iprot.ReadStringAsync(cancellationToken);
                    _val9 = new global::Apache.Hive.Service.Rpc.Thrift.TTypeQualifierValue();
                    await _val9.ReadAsync(iprot, cancellationToken);
                    Qualifiers[_key8] = _val9;
                  }
                  await iprot.ReadMapEndAsync(cancellationToken);
                }
                isset_qualifiers = true;
              }
              else
              {
                await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
              }
              break;
            default:
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
              break;
          }

          await iprot.ReadFieldEndAsync(cancellationToken);
        }

        await iprot.ReadStructEndAsync(cancellationToken);
        if (!isset_qualifiers)
        {
          throw new TProtocolException(TProtocolException.INVALID_DATA);
        }
      }
      finally
      {
        iprot.DecrementRecursionDepth();
      }
    }

    public async global::System.Threading.Tasks.Task WriteAsync(TProtocol oprot, CancellationToken cancellationToken)
    {
      oprot.IncrementRecursionDepth();
      try
      {
        var tmp10 = new TStruct("TTypeQualifiers");
        await oprot.WriteStructBeginAsync(tmp10, cancellationToken);
        var tmp11 = new TField();
        if ((Qualifiers != null))
        {
          tmp11.Name = "qualifiers";
          tmp11.Type = TType.Map;
          tmp11.ID = 1;
          await oprot.WriteFieldBeginAsync(tmp11, cancellationToken);
          await oprot.WriteMapBeginAsync(new TMap(TType.String, TType.Struct, Qualifiers.Count), cancellationToken);
          foreach (string _iter12 in Qualifiers.Keys)
          {
            await oprot.WriteStringAsync(_iter12, cancellationToken);
            await Qualifiers[_iter12].WriteAsync(oprot, cancellationToken);
          }
          await oprot.WriteMapEndAsync(cancellationToken);
          await oprot.WriteFieldEndAsync(cancellationToken);
        }
        await oprot.WriteFieldStopAsync(cancellationToken);
        await oprot.WriteStructEndAsync(cancellationToken);
      }
      finally
      {
        oprot.DecrementRecursionDepth();
      }
    }

    public override bool Equals(object that)
    {
      if (!(that is TTypeQualifiers other)) return false;
      if (ReferenceEquals(this, other)) return true;
      return TCollections.Equals(Qualifiers, other.Qualifiers);
    }

    public override int GetHashCode() {
      int hashcode = 157;
      unchecked {
        if ((Qualifiers != null))
        {
          hashcode = (hashcode * 397) + TCollections.GetHashCode(Qualifiers);
        }
      }
      return hashcode;
    }

    public override string ToString()
    {
      var tmp13 = new StringBuilder("TTypeQualifiers(");
      if ((Qualifiers != null))
      {
        tmp13.Append(", Qualifiers: ");
        Qualifiers.ToString(tmp13);
      }
      tmp13.Append(')');
      return tmp13.ToString();
    }
  }

}
