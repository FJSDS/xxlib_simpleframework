﻿using System;
namespace WEB
{
    public static class PkgGenMd5
    {
        public const string value = "493c5cdfff1560d487bb7c021cd017bc"; 
    }

    /// <summary>
    /// 管理人员
    /// </summary>
    public partial class Manager : Tables.manager
    {
        /// <summary>
        /// 当前令牌( 页面每次 Load 时与存放于 Session 中的值做对比用 )
        /// </summary>
        public string token;
        /// <summary>
        /// 最后访问的时间点( 页面每次 Load 时更新该值, 用于超时判断 )
        /// </summary>
        public DateTime lastVisitTime;

        public override ushort GetPackageId()
        {
            return xx.TypeId<Manager>.value;
        }

        public override void ToBBuffer(xx.BBuffer bb)
        {
            base.ToBBuffer(bb);
            bb.Write(this.token);
            bb.Write(this.lastVisitTime);
        }

        public override void FromBBuffer(xx.BBuffer bb)
        {
            base.FromBBuffer(bb);
            bb.readLengthLimit = 0;
            bb.Read(ref this.token);
            bb.Read(ref this.lastVisitTime);
        }
        public override void ToString(System.Text.StringBuilder s)
        {
            if (__toStringing)
            {
        	    s.Append("[ \"***** recursived *****\" ]");
        	    return;
            }
            else __toStringing = true;

            s.Append("{ \"pkgTypeName\":\"Manager\", \"pkgTypeId\":" + GetPackageId());
            ToStringCore(s);
            s.Append(" }");

            __toStringing = false;
        }
        public override void ToStringCore(System.Text.StringBuilder s)
        {
            base.ToStringCore(s);
            if (token != null) s.Append(", \"token\":\"" + token.ToString() + "\"");
            else s.Append(", \"token\":nil");
            s.Append(", \"lastVisitTime\":" + lastVisitTime.ToString());
        }
        public override string ToString()
        {
            var sb = new System.Text.StringBuilder();
            ToString(sb);
            return sb.ToString();
        }
        public override void MySqlAppend(System.Text.StringBuilder sb, bool ignoreReadOnly)
        {
            base.MySqlAppend(sb, ignoreReadOnly);
        }
    }
    /// <summary>
    /// 身份
    /// </summary>
    public partial class Role : Tables.role
    {

        public override ushort GetPackageId()
        {
            return xx.TypeId<Role>.value;
        }

        public override void ToBBuffer(xx.BBuffer bb)
        {
            base.ToBBuffer(bb);
        }

        public override void FromBBuffer(xx.BBuffer bb)
        {
            base.FromBBuffer(bb);
        }
        public override void ToString(System.Text.StringBuilder s)
        {
            if (__toStringing)
            {
        	    s.Append("[ \"***** recursived *****\" ]");
        	    return;
            }
            else __toStringing = true;

            s.Append("{ \"pkgTypeName\":\"Role\", \"pkgTypeId\":" + GetPackageId());
            ToStringCore(s);
            s.Append(" }");

            __toStringing = false;
        }
        public override void ToStringCore(System.Text.StringBuilder s)
        {
            base.ToStringCore(s);
        }
        public override string ToString()
        {
            var sb = new System.Text.StringBuilder();
            ToString(sb);
            return sb.ToString();
        }
        public override void MySqlAppend(System.Text.StringBuilder sb, bool ignoreReadOnly)
        {
            base.MySqlAppend(sb, ignoreReadOnly);
        }
    }
    /// <summary>
    /// 权限
    /// </summary>
    public partial class Permission : Tables.permission
    {

        public override ushort GetPackageId()
        {
            return xx.TypeId<Permission>.value;
        }

        public override void ToBBuffer(xx.BBuffer bb)
        {
            base.ToBBuffer(bb);
        }

        public override void FromBBuffer(xx.BBuffer bb)
        {
            base.FromBBuffer(bb);
        }
        public override void ToString(System.Text.StringBuilder s)
        {
            if (__toStringing)
            {
        	    s.Append("[ \"***** recursived *****\" ]");
        	    return;
            }
            else __toStringing = true;

            s.Append("{ \"pkgTypeName\":\"Permission\", \"pkgTypeId\":" + GetPackageId());
            ToStringCore(s);
            s.Append(" }");

            __toStringing = false;
        }
        public override void ToStringCore(System.Text.StringBuilder s)
        {
            base.ToStringCore(s);
        }
        public override string ToString()
        {
            var sb = new System.Text.StringBuilder();
            ToString(sb);
            return sb.ToString();
        }
        public override void MySqlAppend(System.Text.StringBuilder sb, bool ignoreReadOnly)
        {
            base.MySqlAppend(sb, ignoreReadOnly);
        }
    }
    /// <summary>
    /// 管理人员_身份_绑定
    /// </summary>
    public partial class BindManagerRole : Tables.manager_role
    {

        public override ushort GetPackageId()
        {
            return xx.TypeId<BindManagerRole>.value;
        }

        public override void ToBBuffer(xx.BBuffer bb)
        {
            base.ToBBuffer(bb);
        }

        public override void FromBBuffer(xx.BBuffer bb)
        {
            base.FromBBuffer(bb);
        }
        public override void ToString(System.Text.StringBuilder s)
        {
            if (__toStringing)
            {
        	    s.Append("[ \"***** recursived *****\" ]");
        	    return;
            }
            else __toStringing = true;

            s.Append("{ \"pkgTypeName\":\"BindManagerRole\", \"pkgTypeId\":" + GetPackageId());
            ToStringCore(s);
            s.Append(" }");

            __toStringing = false;
        }
        public override void ToStringCore(System.Text.StringBuilder s)
        {
            base.ToStringCore(s);
        }
        public override string ToString()
        {
            var sb = new System.Text.StringBuilder();
            ToString(sb);
            return sb.ToString();
        }
        public override void MySqlAppend(System.Text.StringBuilder sb, bool ignoreReadOnly)
        {
            base.MySqlAppend(sb, ignoreReadOnly);
        }
    }
    /// <summary>
    /// 身份_权限_绑定
    /// </summary>
    public partial class BindRolePermission : Tables.role_permission
    {

        public override ushort GetPackageId()
        {
            return xx.TypeId<BindRolePermission>.value;
        }

        public override void ToBBuffer(xx.BBuffer bb)
        {
            base.ToBBuffer(bb);
        }

        public override void FromBBuffer(xx.BBuffer bb)
        {
            base.FromBBuffer(bb);
        }
        public override void ToString(System.Text.StringBuilder s)
        {
            if (__toStringing)
            {
        	    s.Append("[ \"***** recursived *****\" ]");
        	    return;
            }
            else __toStringing = true;

            s.Append("{ \"pkgTypeName\":\"BindRolePermission\", \"pkgTypeId\":" + GetPackageId());
            ToStringCore(s);
            s.Append(" }");

            __toStringing = false;
        }
        public override void ToStringCore(System.Text.StringBuilder s)
        {
            base.ToStringCore(s);
        }
        public override string ToString()
        {
            var sb = new System.Text.StringBuilder();
            ToString(sb);
            return sb.ToString();
        }
        public override void MySqlAppend(System.Text.StringBuilder sb, bool ignoreReadOnly)
        {
            base.MySqlAppend(sb, ignoreReadOnly);
        }
    }
namespace Tables
{
    /// <summary>
    /// 管理人员表
    /// </summary>
    public partial class manager : xx.Object
    {
        public int id;
        public string username;
        public string password;

        public override ushort GetPackageId()
        {
            return xx.TypeId<manager>.value;
        }

        public override void ToBBuffer(xx.BBuffer bb)
        {
            bb.Write(this.id);
            bb.Write(this.username);
            bb.Write(this.password);
        }

        public override void FromBBuffer(xx.BBuffer bb)
        {
            bb.Read(ref this.id);
            bb.readLengthLimit = 0;
            bb.Read(ref this.username);
            bb.readLengthLimit = 0;
            bb.Read(ref this.password);
        }
        public override void ToString(System.Text.StringBuilder s)
        {
            if (__toStringing)
            {
        	    s.Append("[ \"***** recursived *****\" ]");
        	    return;
            }
            else __toStringing = true;

            s.Append("{ \"pkgTypeName\":\"Tables.manager\", \"pkgTypeId\":" + GetPackageId());
            ToStringCore(s);
            s.Append(" }");

            __toStringing = false;
        }
        public override void ToStringCore(System.Text.StringBuilder s)
        {
            s.Append(", \"id\":" + id.ToString());
            if (username != null) s.Append(", \"username\":\"" + username.ToString() + "\"");
            else s.Append(", \"username\":nil");
            if (password != null) s.Append(", \"password\":\"" + password.ToString() + "\"");
            else s.Append(", \"password\":nil");
        }
        public override string ToString()
        {
            var sb = new System.Text.StringBuilder();
            ToString(sb);
            return sb.ToString();
        }
        public override void MySqlAppend(System.Text.StringBuilder sb, bool ignoreReadOnly)
        {
            sb.Append("(");
            if (!ignoreReadOnly)
            {
            sb.Append(this.id);
            sb.Append(", ");
            }
            sb.Append(this.username == null ? "null" : ("'" + this.username.Replace("'", "''") + "'"));
            sb.Append(", ");
            sb.Append(this.password == null ? "null" : ("'" + this.password.Replace("'", "''") + "'"));
            sb.Append(", ");
            sb.Length -= 2;
            sb.Append(")");

        }
    }
    /// <summary>
    /// 管理人员_身份_绑定表
    /// </summary>
    public partial class manager_role : xx.Object
    {
        public int manager_id;
        public int role_id;

        public override ushort GetPackageId()
        {
            return xx.TypeId<manager_role>.value;
        }

        public override void ToBBuffer(xx.BBuffer bb)
        {
            bb.Write(this.manager_id);
            bb.Write(this.role_id);
        }

        public override void FromBBuffer(xx.BBuffer bb)
        {
            bb.Read(ref this.manager_id);
            bb.Read(ref this.role_id);
        }
        public override void ToString(System.Text.StringBuilder s)
        {
            if (__toStringing)
            {
        	    s.Append("[ \"***** recursived *****\" ]");
        	    return;
            }
            else __toStringing = true;

            s.Append("{ \"pkgTypeName\":\"Tables.manager_role\", \"pkgTypeId\":" + GetPackageId());
            ToStringCore(s);
            s.Append(" }");

            __toStringing = false;
        }
        public override void ToStringCore(System.Text.StringBuilder s)
        {
            s.Append(", \"manager_id\":" + manager_id.ToString());
            s.Append(", \"role_id\":" + role_id.ToString());
        }
        public override string ToString()
        {
            var sb = new System.Text.StringBuilder();
            ToString(sb);
            return sb.ToString();
        }
        public override void MySqlAppend(System.Text.StringBuilder sb, bool ignoreReadOnly)
        {
            sb.Append("(");
            sb.Append(this.manager_id);
            sb.Append(", ");
            sb.Append(this.role_id);
            sb.Append(", ");
            sb.Length -= 2;
            sb.Append(")");

        }
    }
    /// <summary>
    /// 权限表
    /// </summary>
    public partial class permission : xx.Object
    {
        public int id;
        public string group;
        public string name;
        public string desc;

        public override ushort GetPackageId()
        {
            return xx.TypeId<permission>.value;
        }

        public override void ToBBuffer(xx.BBuffer bb)
        {
            bb.Write(this.id);
            bb.Write(this.group);
            bb.Write(this.name);
            bb.Write(this.desc);
        }

        public override void FromBBuffer(xx.BBuffer bb)
        {
            bb.Read(ref this.id);
            bb.readLengthLimit = 0;
            bb.Read(ref this.group);
            bb.readLengthLimit = 0;
            bb.Read(ref this.name);
            bb.readLengthLimit = 0;
            bb.Read(ref this.desc);
        }
        public override void ToString(System.Text.StringBuilder s)
        {
            if (__toStringing)
            {
        	    s.Append("[ \"***** recursived *****\" ]");
        	    return;
            }
            else __toStringing = true;

            s.Append("{ \"pkgTypeName\":\"Tables.permission\", \"pkgTypeId\":" + GetPackageId());
            ToStringCore(s);
            s.Append(" }");

            __toStringing = false;
        }
        public override void ToStringCore(System.Text.StringBuilder s)
        {
            s.Append(", \"id\":" + id.ToString());
            if (group != null) s.Append(", \"group\":\"" + group.ToString() + "\"");
            else s.Append(", \"group\":nil");
            if (name != null) s.Append(", \"name\":\"" + name.ToString() + "\"");
            else s.Append(", \"name\":nil");
            if (desc != null) s.Append(", \"desc\":\"" + desc.ToString() + "\"");
            else s.Append(", \"desc\":nil");
        }
        public override string ToString()
        {
            var sb = new System.Text.StringBuilder();
            ToString(sb);
            return sb.ToString();
        }
        public override void MySqlAppend(System.Text.StringBuilder sb, bool ignoreReadOnly)
        {
            sb.Append("(");
            sb.Append(this.id);
            sb.Append(", ");
            sb.Append(this.group == null ? "null" : ("'" + this.group.Replace("'", "''") + "'"));
            sb.Append(", ");
            sb.Append(this.name == null ? "null" : ("'" + this.name.Replace("'", "''") + "'"));
            sb.Append(", ");
            sb.Append(this.desc == null ? "null" : ("'" + this.desc.Replace("'", "''") + "'"));
            sb.Append(", ");
            sb.Length -= 2;
            sb.Append(")");

        }
    }
    /// <summary>
    /// 管理人员身份表
    /// </summary>
    public partial class role : xx.Object
    {
        public int id;
        public string name;
        public string desc;

        public override ushort GetPackageId()
        {
            return xx.TypeId<role>.value;
        }

        public override void ToBBuffer(xx.BBuffer bb)
        {
            bb.Write(this.id);
            bb.Write(this.name);
            bb.Write(this.desc);
        }

        public override void FromBBuffer(xx.BBuffer bb)
        {
            bb.Read(ref this.id);
            bb.readLengthLimit = 0;
            bb.Read(ref this.name);
            bb.readLengthLimit = 0;
            bb.Read(ref this.desc);
        }
        public override void ToString(System.Text.StringBuilder s)
        {
            if (__toStringing)
            {
        	    s.Append("[ \"***** recursived *****\" ]");
        	    return;
            }
            else __toStringing = true;

            s.Append("{ \"pkgTypeName\":\"Tables.role\", \"pkgTypeId\":" + GetPackageId());
            ToStringCore(s);
            s.Append(" }");

            __toStringing = false;
        }
        public override void ToStringCore(System.Text.StringBuilder s)
        {
            s.Append(", \"id\":" + id.ToString());
            if (name != null) s.Append(", \"name\":\"" + name.ToString() + "\"");
            else s.Append(", \"name\":nil");
            if (desc != null) s.Append(", \"desc\":\"" + desc.ToString() + "\"");
            else s.Append(", \"desc\":nil");
        }
        public override string ToString()
        {
            var sb = new System.Text.StringBuilder();
            ToString(sb);
            return sb.ToString();
        }
        public override void MySqlAppend(System.Text.StringBuilder sb, bool ignoreReadOnly)
        {
            sb.Append("(");
            if (!ignoreReadOnly)
            {
            sb.Append(this.id);
            sb.Append(", ");
            }
            sb.Append(this.name == null ? "null" : ("'" + this.name.Replace("'", "''") + "'"));
            sb.Append(", ");
            sb.Append(this.desc == null ? "null" : ("'" + this.desc.Replace("'", "''") + "'"));
            sb.Append(", ");
            sb.Length -= 2;
            sb.Append(")");

        }
    }
    /// <summary>
    /// 身份_权限_绑定表
    /// </summary>
    public partial class role_permission : xx.Object
    {
        public int role_id;
        public int permission_id;

        public override ushort GetPackageId()
        {
            return xx.TypeId<role_permission>.value;
        }

        public override void ToBBuffer(xx.BBuffer bb)
        {
            bb.Write(this.role_id);
            bb.Write(this.permission_id);
        }

        public override void FromBBuffer(xx.BBuffer bb)
        {
            bb.Read(ref this.role_id);
            bb.Read(ref this.permission_id);
        }
        public override void ToString(System.Text.StringBuilder s)
        {
            if (__toStringing)
            {
        	    s.Append("[ \"***** recursived *****\" ]");
        	    return;
            }
            else __toStringing = true;

            s.Append("{ \"pkgTypeName\":\"Tables.role_permission\", \"pkgTypeId\":" + GetPackageId());
            ToStringCore(s);
            s.Append(" }");

            __toStringing = false;
        }
        public override void ToStringCore(System.Text.StringBuilder s)
        {
            s.Append(", \"role_id\":" + role_id.ToString());
            s.Append(", \"permission_id\":" + permission_id.ToString());
        }
        public override string ToString()
        {
            var sb = new System.Text.StringBuilder();
            ToString(sb);
            return sb.ToString();
        }
        public override void MySqlAppend(System.Text.StringBuilder sb, bool ignoreReadOnly)
        {
            sb.Append("(");
            sb.Append(this.role_id);
            sb.Append(", ");
            sb.Append(this.permission_id);
            sb.Append(", ");
            sb.Length -= 2;
            sb.Append(")");

        }
    }
}
    public static class AllTypes
    {
        public static void Register()
        {
            xx.Object.RegisterInternals();
            xx.Object.Register<Manager>(3);
            xx.Object.Register<Tables.manager>(4);
            xx.Object.Register<Role>(5);
            xx.Object.Register<Tables.role>(11);
            xx.Object.Register<Permission>(6);
            xx.Object.Register<Tables.permission>(10);
            xx.Object.Register<BindManagerRole>(7);
            xx.Object.Register<Tables.manager_role>(9);
            xx.Object.Register<BindRolePermission>(8);
            xx.Object.Register<Tables.role_permission>(12);
        }
    }
}
