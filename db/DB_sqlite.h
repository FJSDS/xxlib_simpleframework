﻿#pragma once
#include "DB_class.h"
#include "xx_sqlite.h"

namespace DB
{
    // 游戏相关
    class SQLiteGameFuncs : xx::Object
    {
    public:
		xx::SQLite& sqlite;
		xx::SQLiteString s;

		inline SQLiteGameFuncs(xx::SQLite& sqlite)
            : xx::Object(sqlite.mempool)
            , sqlite(sqlite)
            , s(sqlite.mempool)
        {
        }


        xx::SQLiteQuery_p query_CreateTable_game_account;
        inline void CreateTable_game_account()
        {

			if (!this->query_CreateTable_game_account)
			{
				this->query_CreateTable_game_account = this->sqlite.CreateQuery(R"=-=(
CREATE TABLE [game_account](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, 
    [username] TEXT(50) NOT NULL UNIQUE, 
    [password] TEXT(50) NOT NULL
);)=-=");
			}
            this->query_CreateTable_game_account->Execute();
        }


        xx::SQLiteQuery_p query_SelectAccountByUsername;
        // 根据用户名查找并返回账号. 未找到将返回 null
        template<typename UsernameType_String>
        inline DB::Game::Account_p SelectAccountByUsername
        (
            UsernameType_String const& username
        )
        {

			if (!this->query_SelectAccountByUsername)
			{
				this->query_SelectAccountByUsername = this->sqlite.CreateQuery(R"=-=(
    select [id], [username], [password]
      from [game_account]
     where [username] = ?)=-=");
			}
            DB::Game::Account_p rtv;
            this->query_SelectAccountByUsername->SetParameters(username);
			this->query_SelectAccountByUsername->Execute([&](xx::SQLiteReader& sr)
            {
                assert(!rtv);
                this->mempool->MPCreateTo(rtv);
                rtv->id = sr.ReadInt64(0);
                rtv->username = this->mempool->MPCreate<xx::String>(sr.ReadString(1));
                rtv->password = this->mempool->MPCreate<xx::String>(sr.ReadString(2));
            });
            return rtv;
        }
    };

    using SQLiteGameFuncs_p = xx::Ptr<SQLiteGameFuncs>;
	using SQLiteGameFuncs_r = xx::Ref<SQLiteGameFuncs>;

    // 管理后台相关
    class SQLiteManageFuncs : xx::Object
    {
    public:
		xx::SQLite& sqlite;
		xx::SQLiteString s;

		inline SQLiteManageFuncs(xx::SQLite& sqlite)
            : xx::Object(sqlite.mempool)
            , sqlite(sqlite)
            , s(sqlite.mempool)
        {
        }


        xx::SQLiteQuery_p query_CreateTable_manage_account;
        inline void CreateTable_manage_account()
        {

			if (!this->query_CreateTable_manage_account)
			{
				this->query_CreateTable_manage_account = this->sqlite.CreateQuery(R"=-=(
CREATE TABLE [manage_account](
    [id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE, 
    [username] TEXT(50) NOT NULL UNIQUE, 
    [password] TEXT(50) NOT NULL
);)=-=");
			}
            this->query_CreateTable_manage_account->Execute();
        }


        xx::SQLiteQuery_p query_CreateTable_manage_permission;
        inline void CreateTable_manage_permission()
        {

			if (!this->query_CreateTable_manage_permission)
			{
				this->query_CreateTable_manage_permission = this->sqlite.CreateQuery(R"=-=(
CREATE TABLE [manage_permission](
    [id] INTEGER PRIMARY KEY NOT NULL UNIQUE, 
    [name] TEXT(50) NOT NULL, 
    [desc] TEXT(250) NOT NULL, 
    [group] TEXT(50) NOT NULL, 
    UNIQUE([name], [group])
);)=-=");
			}
            this->query_CreateTable_manage_permission->Execute();
        }


        xx::SQLiteQuery_p query_CreateTable_manage_role;
        inline void CreateTable_manage_role()
        {

			if (!this->query_CreateTable_manage_role)
			{
				this->query_CreateTable_manage_role = this->sqlite.CreateQuery(R"=-=(
CREATE TABLE [manage_role](
    [id] INTEGER PRIMARY KEY NOT NULL UNIQUE, 
    [name] TEXT(50) NOT NULL UNIQUE, 
    [desc] TEXT(250) NOT NULL
);)=-=");
			}
            this->query_CreateTable_manage_role->Execute();
        }


        xx::SQLiteQuery_p query_CreateTable_manage_bind_role_permission;
        inline void CreateTable_manage_bind_role_permission()
        {

			if (!this->query_CreateTable_manage_bind_role_permission)
			{
				this->query_CreateTable_manage_bind_role_permission = this->sqlite.CreateQuery(R"=-=(
CREATE TABLE [manage_bind_role_permission](
    [role_id] INTEGER NOT NULL REFERENCES manage_role([id]), 
    [permission_id] INTEGER NOT NULL REFERENCES manage_permission([id]), 
    PRIMARY KEY([role_id], [permission_id])
);)=-=");
			}
            this->query_CreateTable_manage_bind_role_permission->Execute();
        }


        xx::SQLiteQuery_p query_CreateTable_manage_bind_account_role;
        inline void CreateTable_manage_bind_account_role()
        {

			if (!this->query_CreateTable_manage_bind_account_role)
			{
				this->query_CreateTable_manage_bind_account_role = this->sqlite.CreateQuery(R"=-=(
CREATE TABLE [manage_bind_account_role](
    [account_id] INTEGER NOT NULL REFERENCES manage_account([id]), 
    [role_id] INTEGER NOT NULL REFERENCES manage_role([id]), 
    PRIMARY KEY([account_id], [role_id])
);)=-=");
			}
            this->query_CreateTable_manage_bind_account_role->Execute();
        }


        xx::SQLiteQuery_p query_InsertAccount;
        // 插入一条 账号. 可能因为 username 已存在而失败
        template<typename UsernameType_String
            ,typename PasswordType_String>
        inline void InsertAccount
        (
            UsernameType_String const& username,
            PasswordType_String const& password
        )
        {

			if (!this->query_InsertAccount)
			{
				this->query_InsertAccount = this->sqlite.CreateQuery(R"=-=(insert into [manage_account] ([username], [password]) values (?, ?))=-=");
			}
            this->query_InsertAccount->SetParameters(username, password);
            this->query_InsertAccount->Execute();
        }


        xx::SQLiteQuery_p query_InsertPermission;
        // 插入一条 权限. 可能因为 name 已存在而失败
        template<typename IdType_Int64
            ,typename NameType_String
            ,typename GroupType_String
            ,typename DescType_String>
        inline void InsertPermission
        (
            IdType_Int64 const& id,
            NameType_String const& name,
            GroupType_String const& group,
            DescType_String const& desc
        )
        {

			if (!this->query_InsertPermission)
			{
				this->query_InsertPermission = this->sqlite.CreateQuery(R"=-=(insert into [manage_permission] ([id], [name], [group], [desc]) values (?, ?, ?, ?))=-=");
			}
            this->query_InsertPermission->SetParameters(id, name, group, desc);
            this->query_InsertPermission->Execute();
        }


        xx::SQLiteQuery_p query_InsertRole;
        // 插入一条 身份. 可能因为 id 已存在, name 已存在而失败
        template<typename IdType_Int64
            ,typename NameType_String
            ,typename DescType_String>
        inline void InsertRole
        (
            IdType_Int64 const& id,
            NameType_String const& name,
            DescType_String const& desc
        )
        {

			if (!this->query_InsertRole)
			{
				this->query_InsertRole = this->sqlite.CreateQuery(R"=-=(insert into [manage_role] ([id], [name], [desc]) values (?, ?, ?))=-=");
			}
            this->query_InsertRole->SetParameters(id, name, desc);
            this->query_InsertRole->Execute();
        }


        xx::SQLiteQuery_p query_InsertBindAccountRole;
        // 插入一条 账号.身份 绑定
        template<typename AccountIdType_Int64
            ,typename RoleIdType_Int64>
        inline void InsertBindAccountRole
        (
            AccountIdType_Int64 const& accountId,
            RoleIdType_Int64 const& roleId
        )
        {

			if (!this->query_InsertBindAccountRole)
			{
				this->query_InsertBindAccountRole = this->sqlite.CreateQuery(R"=-=(insert into [manage_bind_account_role] ([account_id], [role_id]) values (?, ?))=-=");
			}
            this->query_InsertBindAccountRole->SetParameters(accountId, roleId);
            this->query_InsertBindAccountRole->Execute();
        }


        xx::SQLiteQuery_p query_InsertBindRolePermission;
        // 插入一条 身份.权限 绑定
        template<typename RoleIdType_Int64
            ,typename PermissionIdType_Int64>
        inline void InsertBindRolePermission
        (
            RoleIdType_Int64 const& roleId,
            PermissionIdType_Int64 const& permissionId
        )
        {

			if (!this->query_InsertBindRolePermission)
			{
				this->query_InsertBindRolePermission = this->sqlite.CreateQuery(R"=-=(insert into [manage_bind_role_permission] ([role_id], [permission_id]) values (?, ?))=-=");
			}
            this->query_InsertBindRolePermission->SetParameters(roleId, permissionId);
            this->query_InsertBindRolePermission->Execute();
        }


        xx::SQLiteQuery_p query_UpdateAccount_ChangePassword;
        // 改密码. 可能因 找不到 id 而失败
        template<typename IdType_Int64
            ,typename NewPasswordType_String>
        inline void UpdateAccount_ChangePassword
        (
            IdType_Int64 const& id,
            NewPasswordType_String const& newPassword
        )
        {

			if (!this->query_UpdateAccount_ChangePassword)
			{
				this->query_UpdateAccount_ChangePassword = this->sqlite.CreateQuery(R"=-=(update [manage_account] set [password] = ? where [id] = ?)=-=");
			}
            this->query_UpdateAccount_ChangePassword->SetParameters(newPassword, id);
            this->query_UpdateAccount_ChangePassword->Execute();
        }


        xx::SQLiteQuery_p query_UpdateAccount_ChangeUsername;
        // 改用户名. 可能因 找不到 id 或 新 username 已存在而失败
        template<typename IdType_Int64
            ,typename NewUsernameType_String>
        inline void UpdateAccount_ChangeUsername
        (
            IdType_Int64 const& id,
            NewUsernameType_String const& newUsername
        )
        {

			if (!this->query_UpdateAccount_ChangeUsername)
			{
				this->query_UpdateAccount_ChangeUsername = this->sqlite.CreateQuery(R"=-=(update [manage_account] set [username] = ? where [id] = ?)=-=");
			}
            this->query_UpdateAccount_ChangeUsername->SetParameters(newUsername, id);
            this->query_UpdateAccount_ChangeUsername->Execute();
        }


        xx::SQLiteQuery_p query_UpdateRole;
        // 更新 身份 数据. 可能因 找不到 id 或 新 name 已存在而失败
        template<typename IdType_Int64
            ,typename NewNameType_String
            ,typename NewDescType_String>
        inline void UpdateRole
        (
            IdType_Int64 const& id,
            NewNameType_String const& newName,
            NewDescType_String const& newDesc
        )
        {

			if (!this->query_UpdateRole)
			{
				this->query_UpdateRole = this->sqlite.CreateQuery(R"=-=(update [manage_role] set [name] = ?, [desc] = ? where [id] = ?)=-=");
			}
            this->query_UpdateRole->SetParameters(newName, newDesc, id);
            this->query_UpdateRole->Execute();
        }


        xx::SQLiteQuery_p query_UpdatePermission;
        // 更新 权限 数据. 可能因 找不到 id 或 新 name 已存在而失败
        template<typename IdType_Int64
            ,typename NewGroupType_String
            ,typename NewNameType_String
            ,typename NewDescType_String>
        inline void UpdatePermission
        (
            IdType_Int64 const& id,
            NewGroupType_String const& newGroup,
            NewNameType_String const& newName,
            NewDescType_String const& newDesc
        )
        {

			if (!this->query_UpdatePermission)
			{
				this->query_UpdatePermission = this->sqlite.CreateQuery(R"=-=(update [manage_permission] set [group] = ?, [name] = ?, [desc] = ? where [id] = ?)=-=");
			}
            this->query_UpdatePermission->SetParameters(newGroup, newName, newDesc, id);
            this->query_UpdatePermission->Execute();
        }


        xx::SQLiteQuery_p query_DeleteBindAccountRoleByAccountId;
        // 根据 accountId 删掉 账号.身份 绑定数据
        template<typename AccountIdType_Int64>
        inline void DeleteBindAccountRoleByAccountId
        (
            AccountIdType_Int64 const& accountId
        )
        {

			if (!this->query_DeleteBindAccountRoleByAccountId)
			{
				this->query_DeleteBindAccountRoleByAccountId = this->sqlite.CreateQuery(R"=-=(delete from [manage_bind_account_role] where [account_id] = ?)=-=");
			}
            this->query_DeleteBindAccountRoleByAccountId->SetParameters(accountId);
            this->query_DeleteBindAccountRoleByAccountId->Execute();
        }


        xx::SQLiteQuery_p query_DeleteBindAccountRoleByRoleId;
        // 根据 roleId 删掉 账号.身份 绑定数据
        template<typename RoleIdType_Int64>
        inline void DeleteBindAccountRoleByRoleId
        (
            RoleIdType_Int64 const& roleId
        )
        {

			if (!this->query_DeleteBindAccountRoleByRoleId)
			{
				this->query_DeleteBindAccountRoleByRoleId = this->sqlite.CreateQuery(R"=-=(delete from [manage_bind_account_role] where [role_id] = ?)=-=");
			}
            this->query_DeleteBindAccountRoleByRoleId->SetParameters(roleId);
            this->query_DeleteBindAccountRoleByRoleId->Execute();
        }


        xx::SQLiteQuery_p query_DeleteBindRolePermissionByRoleId;
        // 根据 roleId 删掉 身份.权限 绑定数据
        template<typename RoleIdType_Int64>
        inline void DeleteBindRolePermissionByRoleId
        (
            RoleIdType_Int64 const& roleId
        )
        {

			if (!this->query_DeleteBindRolePermissionByRoleId)
			{
				this->query_DeleteBindRolePermissionByRoleId = this->sqlite.CreateQuery(R"=-=(delete from [manage_bind_role_permission] where [role_id] = ?)=-=");
			}
            this->query_DeleteBindRolePermissionByRoleId->SetParameters(roleId);
            this->query_DeleteBindRolePermissionByRoleId->Execute();
        }


        xx::SQLiteQuery_p query_DeleteAccount;
        // 根据主键删一条 账号. 需要先删相关绑定, 否则可能失败. 也有可能 id 找不到而没删到数据. 要用 GetAffectedRows 的值来判断
        template<typename IdType_Int64>
        inline void DeleteAccount
        (
            IdType_Int64 const& id
        )
        {

			if (!this->query_DeleteAccount)
			{
				this->query_DeleteAccount = this->sqlite.CreateQuery(R"=-=(delete from [manage_account] where [id] = ?)=-=");
			}
            this->query_DeleteAccount->SetParameters(id);
            this->query_DeleteAccount->Execute();
        }


        xx::SQLiteQuery_p query_DeletePermission;
        // 根据主键删一条 权限. 需要先删掉相关绑定, 否则可能失败
        template<typename IdType_Int64>
        inline void DeletePermission
        (
            IdType_Int64 const& id
        )
        {

			if (!this->query_DeletePermission)
			{
				this->query_DeletePermission = this->sqlite.CreateQuery(R"=-=(delete from [manage_permission] where [id] = ?)=-=");
			}
            this->query_DeletePermission->SetParameters(id);
            this->query_DeletePermission->Execute();
        }


        xx::SQLiteQuery_p query_DeleteRole;
        // 根据主键删一条 角色. 需要先删掉相关绑定, 否则可能失败
        template<typename IdType_Int64>
        inline void DeleteRole
        (
            IdType_Int64 const& id
        )
        {

			if (!this->query_DeleteRole)
			{
				this->query_DeleteRole = this->sqlite.CreateQuery(R"=-=(delete from [manage_role] where [id] = ?)=-=");
			}
            this->query_DeleteRole->SetParameters(id);
            this->query_DeleteRole->Execute();
        }


        xx::SQLiteQuery_p query_SelectAccounts;
        // 获取账号表所有数据
        inline xx::List_p<DB::Manage::Account_p> SelectAccounts()
        {

			if (!this->query_SelectAccounts)
			{
				this->query_SelectAccounts = this->sqlite.CreateQuery(R"=-=(select [id], [username], [password] from [manage_account])=-=");
			}
            xx::List_p<DB::Manage::Account_p> rtv;
            this->mempool->MPCreateTo(rtv);
			this->query_SelectAccounts->Execute([&](xx::SQLiteReader& sr)
            {
				auto& r = rtv->Emplace();
                this->mempool->MPCreateTo(r);
                r->id = sr.ReadInt64(0);
                r->username = this->mempool->MPCreate<xx::String>(sr.ReadString(1));
                r->password = this->mempool->MPCreate<xx::String>(sr.ReadString(2));
            });
			return rtv;
        }


        xx::SQLiteQuery_p query_SelectRoles;
        // 读所有 身份 数据
        inline xx::List_p<DB::Manage::Role_p> SelectRoles()
        {

			if (!this->query_SelectRoles)
			{
				this->query_SelectRoles = this->sqlite.CreateQuery(R"=-=(select [id], [name], [desc] from [manage_role])=-=");
			}
            xx::List_p<DB::Manage::Role_p> rtv;
            this->mempool->MPCreateTo(rtv);
			this->query_SelectRoles->Execute([&](xx::SQLiteReader& sr)
            {
				auto& r = rtv->Emplace();
                this->mempool->MPCreateTo(r);
                r->id = sr.ReadInt32(0);
                if (!sr.IsDBNull(0)) r->name = this->mempool->MPCreate<xx::String>(sr.ReadString(1));
                if (!sr.IsDBNull(0)) r->desc = this->mempool->MPCreate<xx::String>(sr.ReadString(2));
            });
			return rtv;
        }


        xx::SQLiteQuery_p query_SelectPermissions;
        // 读所有权限数据
        inline xx::List_p<DB::Manage::Permission_p> SelectPermissions()
        {

			if (!this->query_SelectPermissions)
			{
				this->query_SelectPermissions = this->sqlite.CreateQuery(R"=-=(select [id], [group], [name], [desc] from [manage_permission])=-=");
			}
            xx::List_p<DB::Manage::Permission_p> rtv;
            this->mempool->MPCreateTo(rtv);
			this->query_SelectPermissions->Execute([&](xx::SQLiteReader& sr)
            {
				auto& r = rtv->Emplace();
                this->mempool->MPCreateTo(r);
                r->id = sr.ReadInt32(0);
                if (!sr.IsDBNull(0)) r->group = this->mempool->MPCreate<xx::String>(sr.ReadString(1));
                if (!sr.IsDBNull(0)) r->name = this->mempool->MPCreate<xx::String>(sr.ReadString(2));
                if (!sr.IsDBNull(0)) r->desc = this->mempool->MPCreate<xx::String>(sr.ReadString(3));
            });
			return rtv;
        }


        xx::SQLiteQuery_p query_SelectBindRolePermissions;
        // 读所有 身份 数据
        inline xx::List_p<DB::Manage::BindRolePermission_p> SelectBindRolePermissions()
        {

			if (!this->query_SelectBindRolePermissions)
			{
				this->query_SelectBindRolePermissions = this->sqlite.CreateQuery(R"=-=(select [role_id], [permission_id] from [manage_bind_role_permission])=-=");
			}
            xx::List_p<DB::Manage::BindRolePermission_p> rtv;
            this->mempool->MPCreateTo(rtv);
			this->query_SelectBindRolePermissions->Execute([&](xx::SQLiteReader& sr)
            {
				auto& r = rtv->Emplace();
                this->mempool->MPCreateTo(r);
                r->role_id = sr.ReadInt32(0);
                r->permission_id = sr.ReadInt32(1);
            });
			return rtv;
        }


        xx::SQLiteQuery_p query_SelectBindAccountRoles;
        // 读所有权限数据
        inline xx::List_p<DB::Manage::BindAccountRole_p> SelectBindAccountRoles()
        {

			if (!this->query_SelectBindAccountRoles)
			{
				this->query_SelectBindAccountRoles = this->sqlite.CreateQuery(R"=-=(select [account_id], [role_id] from [manage_bind_account_role])=-=");
			}
            xx::List_p<DB::Manage::BindAccountRole_p> rtv;
            this->mempool->MPCreateTo(rtv);
			this->query_SelectBindAccountRoles->Execute([&](xx::SQLiteReader& sr)
            {
				auto& r = rtv->Emplace();
                this->mempool->MPCreateTo(r);
                r->account_id = sr.ReadInt32(0);
                r->role_id = sr.ReadInt32(1);
            });
			return rtv;
        }


        xx::SQLiteQuery_p query_SelectAccountIdsBySortLimit;
        // 根据排序规则返回 limit 行账号记录.
        template<typename SortType_String
            ,typename LimitType_Int64>
        inline xx::List_p<int64_t> SelectAccountIdsBySortLimit
        (
            SortType_String const& sort,
            LimitType_Int64 const& limit
        )
        {

            this->s->Clear();
            this->s->Append(R"=-=(select [id] from [manage_account] order by )=-=");
            this->s->Append(sort);
            this->s->Append(R"=-=( limit 0, )=-=");
            this->s->Append(limit);
            this->query_SelectAccountIdsBySortLimit = sqlite.CreateQuery(s->C_str(), s->dataLen);
            xx::List_p<int64_t> rtv;
            this->mempool->MPCreateTo(rtv);
            this->query_SelectAccountIdsBySortLimit->Execute([&](xx::SQLiteReader& sr)
            {
				rtv->Add(sr.ReadInt64(0));
            });
			return rtv;
        }


        xx::SQLiteQuery_p query_SelectAccountsByIds;
        // 根据用户 ids 查找并返回一批账号记录.
        template<typename IdsType_List`1>
        inline xx::List_p<DB::Manage::Account_p> SelectAccountsByIds
        (
            IdsType_List`1 const& ids
        )
        {

            this->s->Clear();
            this->s->Append(R"=-=(select [id], [username], '' from [manage_account] where [id] in )=-=");
            this->s->SQLAppend(ids);
            this->query_SelectAccountsByIds = sqlite.CreateQuery(s->C_str(), s->dataLen);
            xx::List_p<DB::Manage::Account_p> rtv;
            this->mempool->MPCreateTo(rtv);
			this->query_SelectAccountsByIds->Execute([&](xx::SQLiteReader& sr)
            {
				auto& r = rtv->Emplace();
                this->mempool->MPCreateTo(r);
                r->id = sr.ReadInt64(0);
                r->username = this->mempool->MPCreate<xx::String>(sr.ReadString(1));
                r->password = this->mempool->MPCreate<xx::String>(sr.ReadString(2));
            });
			return rtv;
        }


        xx::SQLiteQuery_p query_SelectAccountByUsername;
        // 根据用户名查找并返回一条账号记录. 未找到将返回 null
        template<typename UsernameType_String>
        inline DB::Manage::Account_p SelectAccountByUsername
        (
            UsernameType_String const& username
        )
        {

			if (!this->query_SelectAccountByUsername)
			{
				this->query_SelectAccountByUsername = this->sqlite.CreateQuery(R"=-=(select [id], [username], [password] from [manage_account] where [username] = ?)=-=");
			}
            DB::Manage::Account_p rtv;
            this->query_SelectAccountByUsername->SetParameters(username);
			this->query_SelectAccountByUsername->Execute([&](xx::SQLiteReader& sr)
            {
                assert(!rtv);
                this->mempool->MPCreateTo(rtv);
                rtv->id = sr.ReadInt64(0);
                rtv->username = this->mempool->MPCreate<xx::String>(sr.ReadString(1));
                rtv->password = this->mempool->MPCreate<xx::String>(sr.ReadString(2));
            });
            return rtv;
        }


        xx::SQLiteQuery_p query_SelectPermissionIdsByAccountId;
        // 根据 accountId 获取 身份id列表 以及 去重后的 权限id列表
        template<typename AccountIdType_Int64>
        inline xx::List_p<int64_t> SelectPermissionIdsByAccountId
        (
            AccountIdType_Int64 const& accountId
        )
        {

			if (!this->query_SelectPermissionIdsByAccountId)
			{
				this->query_SelectPermissionIdsByAccountId = this->sqlite.CreateQuery(R"=-=(
select distinct b.[permission_id]
  from [manage_bind_account_role] a
  join [manage_bind_role_permission] b
    on a.[role_id] = b.[role_id]
 where a.[account_id] = ?;)=-=");
			}
            xx::List_p<int64_t> rtv;
            this->mempool->MPCreateTo(rtv);
            this->query_SelectPermissionIdsByAccountId->SetParameters(accountId);
            this->query_SelectPermissionIdsByAccountId->Execute([&](xx::SQLiteReader& sr)
            {
				rtv->Add(sr.ReadInt64(0));
            });
			return rtv;
        }


        xx::SQLiteQuery_p query_SelectRoleIdsByAccountId;
        // 根据 accountId 获取 身份id列表
        template<typename AccountIdType_Int64>
        inline xx::List_p<int64_t> SelectRoleIdsByAccountId
        (
            AccountIdType_Int64 const& accountId
        )
        {

			if (!this->query_SelectRoleIdsByAccountId)
			{
				this->query_SelectRoleIdsByAccountId = this->sqlite.CreateQuery(R"=-=(
select [role_id]
  from [manage_bind_account_role]
 where [account_id] = ?;)=-=");
			}
            xx::List_p<int64_t> rtv;
            this->mempool->MPCreateTo(rtv);
            this->query_SelectRoleIdsByAccountId->SetParameters(accountId);
            this->query_SelectRoleIdsByAccountId->Execute([&](xx::SQLiteReader& sr)
            {
				rtv->Add(sr.ReadInt64(0));
            });
			return rtv;
        }
    };

    using SQLiteManageFuncs_p = xx::Ptr<SQLiteManageFuncs>;
	using SQLiteManageFuncs_r = xx::Ref<SQLiteManageFuncs>;

}
