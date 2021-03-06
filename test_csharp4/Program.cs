﻿using System;
public class Foo
{
    public int id;
    public string name;
    public string phone;
    public string token;
    public override string ToString()
    {
        return "foo: id = " + id + ", name = `" + name + "`" + ", phone = `" + phone + "`" + ", token = `" + token + "`";
    }
}

public static class Program
{
    static void Main(string[] args)
    {
        var fd = new xx.DictEx<Foo, int, string, string, string>();
        var f1 = new Foo { id = 1, name = "a", phone = "123", token = Guid.NewGuid().ToString() };
        Console.WriteLine(fd.Add(f1, f1.id, f1.name, f1.phone, f1.token));  // true
        var f2 = new Foo { id = 2, name = "b", phone = "456", token = Guid.NewGuid().ToString() };
        Console.WriteLine(fd.Add(f2, f2.id, f2.name, f2.phone, f2.token));  // true
        var f3 = new Foo { id = 3, name = "c", phone = "789", token = Guid.NewGuid().ToString() };
        Console.WriteLine(fd.Add(f3, f3.id, f3.name, f3.phone, f3.token));  // true

        Console.WriteLine(fd.Add(f1, f1.id, f1.name, f1.phone, f1.token));  // false
        Console.WriteLine(fd.Add(f3, f3.id, f3.name, f3.phone, f3.token));  // false

        Console.WriteLine(fd.Exists1(1));       // true
        Console.WriteLine(fd.Exists2("b"));     // true
        Console.WriteLine(fd.Exists1(3));       // true
        Console.WriteLine(fd.Exists3("123"));   // true
        Console.WriteLine(fd.Exists2("d"));     // false
        Console.WriteLine(fd.Exists3("234"));   // false

        fd.Remove2("a");
        fd.Remove1(2);
        Console.WriteLine(fd.Exists1(1));       // false
        Console.WriteLine(fd.Exists2("b"));     // false

        fd.ForEach(f => { Console.WriteLine(f); }); // 3, c
    }
}
