﻿using System;
using xx;

namespace RPC
{
    public static class MySqlAppendExt
    {
        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, T v, bool ignoreReadOnly = false)
        {
            sb.Append(v);
        }

        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, T? o, bool ignoreReadOnly = false) where T : struct
        {
            if (o.HasValue)
            {
                sb.MySqlAppend(o.Value);
            }
            else
            {
                sb.Append("null");
            }
        }

        public static void MySqlAppend(this System.Text.StringBuilder sb, string v, bool ignoreReadOnly = false)
        {
            sb.Append("'" + v.Replace("'", "''") + "'");
        }

        public static void MySqlAppend(this System.Text.StringBuilder sb, DateTime o, bool ignoreReadOnly = false)
        {
            sb.Append("'" + o.ToString("yyyy-MM-dd HH:mm:ss") + "'");
        }

        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, List<T> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); for (int i = 0; i < os.dataLen; ++i) { sb.MySqlAppend(os[i], ignoreReadOnly); sb.Append(", "); }; sb.Length -= 2; }
        public static void MySqlAppend(this System.Text.StringBuilder sb, List<DateTime> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); sb.Append("( "); for (int i = 0; i < os.dataLen; ++i) { sb.MySqlAppend(os[i]); sb.Append(", "); }; sb.Length -= 2; sb.Append(" )"); }
        public static void MySqlAppend(this System.Text.StringBuilder sb, List<byte> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); sb.Append("( "); for (int i = 0; i < os.dataLen; ++i) { sb.Append(os[i]); sb.Append(", "); }; sb.Length -= 2; sb.Append(" )"); }
        public static void MySqlAppend(this System.Text.StringBuilder sb, List<ushort> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); sb.Append("( "); for (int i = 0; i < os.dataLen; ++i) { sb.Append(os[i]); sb.Append(", "); }; sb.Length -= 2; sb.Append(" )"); }
        public static void MySqlAppend(this System.Text.StringBuilder sb, List<uint> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); sb.Append("( "); for (int i = 0; i < os.dataLen; ++i) { sb.Append(os[i]); sb.Append(", "); }; sb.Length -= 2; sb.Append(" )"); }
        public static void MySqlAppend(this System.Text.StringBuilder sb, List<ulong> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); sb.Append("( "); for (int i = 0; i < os.dataLen; ++i) { sb.Append(os[i]); sb.Append(", "); }; sb.Length -= 2; sb.Append(" )"); }
        public static void MySqlAppend(this System.Text.StringBuilder sb, List<sbyte> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); sb.Append("( "); for (int i = 0; i < os.dataLen; ++i) { sb.Append(os[i]); sb.Append(", "); }; sb.Length -= 2; sb.Append(" )"); }
        public static void MySqlAppend(this System.Text.StringBuilder sb, List<short> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); sb.Append("( "); for (int i = 0; i < os.dataLen; ++i) { sb.Append(os[i]); sb.Append(", "); }; sb.Length -= 2; sb.Append(" )"); }
        public static void MySqlAppend(this System.Text.StringBuilder sb, List<int> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); sb.Append("( "); for (int i = 0; i < os.dataLen; ++i) { sb.Append(os[i]); sb.Append(", "); }; sb.Length -= 2; sb.Append(" )"); }
        public static void MySqlAppend(this System.Text.StringBuilder sb, List<long> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); sb.Append("( "); for (int i = 0; i < os.dataLen; ++i) { sb.Append(os[i]); sb.Append(", "); }; sb.Length -= 2; sb.Append(" )"); }
        public static void MySqlAppend(this System.Text.StringBuilder sb, List<double> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); sb.Append("( "); for (int i = 0; i < os.dataLen; ++i) { sb.Append(os[i]); sb.Append(", "); }; sb.Length -= 2; sb.Append(" )"); }
        public static void MySqlAppend(this System.Text.StringBuilder sb, List<float> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); sb.Append("( "); for (int i = 0; i < os.dataLen; ++i) { sb.Append(os[i]); sb.Append(", "); }; sb.Length -= 2; sb.Append(" )"); }
        public static void MySqlAppend(this System.Text.StringBuilder sb, List<bool> os, bool ignoreReadOnly = false) { if (os == null || os.dataLen == 0) throw new ArgumentNullException(); sb.Append("( "); for (int i = 0; i < os.dataLen; ++i) { sb.Append(os[i]); sb.Append(", "); }; sb.Length -= 2; sb.Append(" )"); }

        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, DB_Manage.MsgResult o, bool ignoreReadOnly = false)
        {
            sb.Append("(");
            sb.Length -= 2;
            sb.Append(")");
        }
        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, Manage_DB.Msg o, bool ignoreReadOnly = false)
        {
            sb.Append("(");
            sb.Length -= 2;
            sb.Append(")");
        }
        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, Login_Client.LoginSuccess o, bool ignoreReadOnly = false)
        {
            sb.Append("(");
            sb.Length -= 2;
            sb.Append(")");
        }
        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, Client_Login.Login o, bool ignoreReadOnly = false)
        {
            sb.Append("(");
            sb.Length -= 2;
            sb.Append(")");
        }
        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, DB_Login.AuthSuccess o, bool ignoreReadOnly = false)
        {
            sb.Append("(");
            sb.Length -= 2;
            sb.Append(")");
        }
        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, Login_DB.Auth o, bool ignoreReadOnly = false)
        {
            sb.Append("(");
            sb.Length -= 2;
            sb.Append(")");
        }
        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, Generic.ServiceInfo o, bool ignoreReadOnly = false)
        {
            sb.Append("(");
            sb.Length -= 2;
            sb.Append(")");
        }
        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, Generic.Error o, bool ignoreReadOnly = false)
        {
            sb.Append("(");
            sb.Length -= 2;
            sb.Append(")");
        }
        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, Generic.Ping o, bool ignoreReadOnly = false)
        {
            sb.Append("(");
            sb.Length -= 2;
            sb.Append(")");
        }
        public static void MySqlAppend<T>(this System.Text.StringBuilder sb, Generic.Pong o, bool ignoreReadOnly = false)
        {
            sb.Append("(");
            sb.Length -= 2;
            sb.Append(")");
        }
    }

}