﻿using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
using MySql.Data.MySqlClient;

public static class Program
{
    ///// <summary>
    ///// 快速执行 sql 的简易封装( 针对 MySqlFuncs ). 返回异常.
    ///// </summary>
    //public static Exception CallMySqlFuncs(Action<PKG.MySqlFuncs> a)
    //{
    //    try
    //    {
    //        using (var conn = new MySqlConnection($"server={"127.0.0.1"};user id={"root"};password={"1"};database={"catch_fish"};port={3306};charset=utf8;sslmode=none"))
    //        {
    //            conn.Open();
    //            var fs = new PKG.MySqlFuncs(conn);
    //            a(fs);
    //        }
    //    }
    //    catch (Exception ex)
    //    {
    //        return ex;
    //    }
    //    return null;
    //}


    static void Main(string[] args)
    {
        PKG.AllTypes.Register();

        //PKG.DataSet ds = new PKG.DataSet();
        //ds.tables = new xx.List<PKG.Table>();

        //var t = new PKG.Table();
        //t.parent = ds;
        //t.columns = new xx.List<PKG.TableColumn>();
        //t.rows = new xx.List<PKG.TableRow>();
        //t.name = "table_1";
        //ds.tables.Add(t);

        //var tc = new PKG.TableColumn();
        //tc.name = "column_1";
        //t.columns.Add(tc);

        //var tr = new PKG.TableRow();
        //tr.values = new xx.List<PKG.TableRowValue>();
        //t.rows.Add(tr);

        //var trv1 = new PKG.TableRowValue_NullableInt();
        //trv1.value = 123;
        //tr.values.Add(trv1);
        //var trv2 = new PKG.TableRowValue_NullableInt();
        //trv1.value = null;
        //tr.values.Add(trv1);

        //Console.WriteLine(ds);

        //var bb = new xx.BBuffer();
        //bb.WriteRoot(ds);

        //Console.WriteLine(bb);


        PKG.AllTypes.Register();
        //var e = CallMySqlFuncs(fs =>
        //{
        //    var db_nodes = fs.SelectNodes<PKG.Tables.node>();
        //    db_nodes.ForEach(o =>
        //    {
        //        Console.WriteLine(o);
        //    });



        //    // 从 mysql 以 PKG.Node 类型读出结果集( 基类是 Tables.node )
        //    var nodes = fs.SelectNodes<PKG.Node>();

        //    // 填充父子关联
        //    nodes.ForEach(node => node.childs = new xx.List<PKG.Node>());
        //    nodes.ForEach(node =>
        //    {
        //        // pid 空者为 root
        //        if (!node.pid.HasValue) return;

        //        // 根据 pid 定位 parent
        //        var idx = nodes.Find(n => n.id == node.pid);

        //        // 填充父子关联
        //        node.parent = nodes[idx];
        //        node.parent.childs.Add(node);
        //    });

        //    // 将 root 序列化成 byte[]
        //    var bb = new xx.BBuffer();
        //    bb.WriteRoot(nodes[0]);
        //    Console.WriteLine(bb);












        //    //var r = fs.SelectFooFoo<PKG.Foo, PKG.FooEx>(1, 2, "");
        //    //Console.WriteLine(r.Item1);
        //    //Console.WriteLine(r.Item2);
        //    //Console.WriteLine(r.Item3);
        //    //Console.WriteLine(r.Item4);

        //    //var foo1 = fs.SelectFoo<PKG.Foo>(1, null, "this is 1 null");
        //    //var foo2 = fs.SelectFoo<PKG.Foo>(2, 12, "this is 2 12");
        //    //foo1.childs = new xx.List<PKG.Foo>();
        //    //foo1.childs.Add(foo2);
        //    //foo2.childs = new xx.List<PKG.Foo>();
        //    //foo2.childs.Add(foo1);

        //    //Console.WriteLine(foo1);

        //    //var bb = new xx.BBuffer();
        //    //bb.WriteRoot(foo1);
        //    //Console.WriteLine(bb);

        //    //PKG.Foo foo3 = null;
        //    //bb.ReadRoot(ref foo3);
        //    //Console.WriteLine(foo3);
        //});
    }
}
