/*
 * Generated by gdbus-codegen 2.46.2. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#ifndef __NET_KHPYLON_YOGA900_GENERATED_CODE_H__
#define __NET_KHPYLON_YOGA900_GENERATED_CODE_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for net.khpylon.yoga900keyboard */

#define KEYBOARD_TYPE_ (keyboard__get_type ())
#define KEYBOARD_(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), KEYBOARD_TYPE_, keyboard))
#define KEYBOARD_IS_(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), KEYBOARD_TYPE_))
#define KEYBOARD__GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), KEYBOARD_TYPE_, keyboardIface))

struct _keyboard;
typedef struct _keyboard keyboard;
typedef struct _keyboardIface keyboardIface;

struct _keyboardIface
{
  GTypeInterface parent_iface;

  gboolean  (*get_laptop_mode) (keyboard *object);

};

GType keyboard__get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *keyboard__interface_info (void);
guint keyboard__override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus property accessors: */
gboolean keyboard__get_laptop_mode (keyboard *object);
void keyboard__set_laptop_mode (keyboard *object, gboolean value);


/* ---- */

#define KEYBOARD_TYPE__PROXY (keyboard__proxy_get_type ())
#define KEYBOARD__PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), KEYBOARD_TYPE__PROXY, keyboardProxy))
#define KEYBOARD__PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), KEYBOARD_TYPE__PROXY, keyboardProxyClass))
#define KEYBOARD__PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), KEYBOARD_TYPE__PROXY, keyboardProxyClass))
#define KEYBOARD_IS__PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), KEYBOARD_TYPE__PROXY))
#define KEYBOARD_IS__PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), KEYBOARD_TYPE__PROXY))

typedef struct _keyboardProxy keyboardProxy;
typedef struct _keyboardProxyClass keyboardProxyClass;
typedef struct _keyboardProxyPrivate keyboardProxyPrivate;

struct _keyboardProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  keyboardProxyPrivate *priv;
};

struct _keyboardProxyClass
{
  GDBusProxyClass parent_class;
};

GType keyboard__proxy_get_type (void) G_GNUC_CONST;

void keyboard__proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
keyboard *keyboard__proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
keyboard *keyboard__proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void keyboard__proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
keyboard *keyboard__proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
keyboard *keyboard__proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define KEYBOARD_TYPE__SKELETON (keyboard__skeleton_get_type ())
#define KEYBOARD__SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), KEYBOARD_TYPE__SKELETON, keyboardSkeleton))
#define KEYBOARD__SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), KEYBOARD_TYPE__SKELETON, keyboardSkeletonClass))
#define KEYBOARD__SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), KEYBOARD_TYPE__SKELETON, keyboardSkeletonClass))
#define KEYBOARD_IS__SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), KEYBOARD_TYPE__SKELETON))
#define KEYBOARD_IS__SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), KEYBOARD_TYPE__SKELETON))

typedef struct _keyboardSkeleton keyboardSkeleton;
typedef struct _keyboardSkeletonClass keyboardSkeletonClass;
typedef struct _keyboardSkeletonPrivate keyboardSkeletonPrivate;

struct _keyboardSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  keyboardSkeletonPrivate *priv;
};

struct _keyboardSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType keyboard__skeleton_get_type (void) G_GNUC_CONST;

keyboard *keyboard__skeleton_new (void);


/* ---- */

#define KEYBOARD_TYPE_OBJECT (keyboard_object_get_type ())
#define KEYBOARD_OBJECT(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), KEYBOARD_TYPE_OBJECT, keyboardObject))
#define KEYBOARD_IS_OBJECT(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), KEYBOARD_TYPE_OBJECT))
#define KEYBOARD_OBJECT_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), KEYBOARD_TYPE_OBJECT, keyboardObject))

struct _keyboardObject;
typedef struct _keyboardObject keyboardObject;
typedef struct _keyboardObjectIface keyboardObjectIface;

struct _keyboardObjectIface
{
  GTypeInterface parent_iface;
};

GType keyboard_object_get_type (void) G_GNUC_CONST;

keyboard *keyboard_object_get_ (keyboardObject *object);
keyboard *keyboard_object_peek_ (keyboardObject *object);

#define KEYBOARD_TYPE_OBJECT_PROXY (keyboard_object_proxy_get_type ())
#define KEYBOARD_OBJECT_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), KEYBOARD_TYPE_OBJECT_PROXY, keyboardObjectProxy))
#define KEYBOARD_OBJECT_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), KEYBOARD_TYPE_OBJECT_PROXY, keyboardObjectProxyClass))
#define KEYBOARD_OBJECT_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), KEYBOARD_TYPE_OBJECT_PROXY, keyboardObjectProxyClass))
#define KEYBOARD_IS_OBJECT_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), KEYBOARD_TYPE_OBJECT_PROXY))
#define KEYBOARD_IS_OBJECT_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), KEYBOARD_TYPE_OBJECT_PROXY))

typedef struct _keyboardObjectProxy keyboardObjectProxy;
typedef struct _keyboardObjectProxyClass keyboardObjectProxyClass;
typedef struct _keyboardObjectProxyPrivate keyboardObjectProxyPrivate;

struct _keyboardObjectProxy
{
  /*< private >*/
  GDBusObjectProxy parent_instance;
  keyboardObjectProxyPrivate *priv;
};

struct _keyboardObjectProxyClass
{
  GDBusObjectProxyClass parent_class;
};

GType keyboard_object_proxy_get_type (void) G_GNUC_CONST;
keyboardObjectProxy *keyboard_object_proxy_new (GDBusConnection *connection, const gchar *object_path);

#define KEYBOARD_TYPE_OBJECT_SKELETON (keyboard_object_skeleton_get_type ())
#define KEYBOARD_OBJECT_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), KEYBOARD_TYPE_OBJECT_SKELETON, keyboardObjectSkeleton))
#define KEYBOARD_OBJECT_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), KEYBOARD_TYPE_OBJECT_SKELETON, keyboardObjectSkeletonClass))
#define KEYBOARD_OBJECT_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), KEYBOARD_TYPE_OBJECT_SKELETON, keyboardObjectSkeletonClass))
#define KEYBOARD_IS_OBJECT_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), KEYBOARD_TYPE_OBJECT_SKELETON))
#define KEYBOARD_IS_OBJECT_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), KEYBOARD_TYPE_OBJECT_SKELETON))

typedef struct _keyboardObjectSkeleton keyboardObjectSkeleton;
typedef struct _keyboardObjectSkeletonClass keyboardObjectSkeletonClass;
typedef struct _keyboardObjectSkeletonPrivate keyboardObjectSkeletonPrivate;

struct _keyboardObjectSkeleton
{
  /*< private >*/
  GDBusObjectSkeleton parent_instance;
  keyboardObjectSkeletonPrivate *priv;
};

struct _keyboardObjectSkeletonClass
{
  GDBusObjectSkeletonClass parent_class;
};

GType keyboard_object_skeleton_get_type (void) G_GNUC_CONST;
keyboardObjectSkeleton *keyboard_object_skeleton_new (const gchar *object_path);
void keyboard_object_skeleton_set_ (keyboardObjectSkeleton *object, keyboard *interface_);

/* ---- */

#define KEYBOARD_TYPE_OBJECT_MANAGER_CLIENT (keyboard_object_manager_client_get_type ())
#define KEYBOARD_OBJECT_MANAGER_CLIENT(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), KEYBOARD_TYPE_OBJECT_MANAGER_CLIENT, keyboardObjectManagerClient))
#define KEYBOARD_OBJECT_MANAGER_CLIENT_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), KEYBOARD_TYPE_OBJECT_MANAGER_CLIENT, keyboardObjectManagerClientClass))
#define KEYBOARD_OBJECT_MANAGER_CLIENT_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), KEYBOARD_TYPE_OBJECT_MANAGER_CLIENT, keyboardObjectManagerClientClass))
#define KEYBOARD_IS_OBJECT_MANAGER_CLIENT(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), KEYBOARD_TYPE_OBJECT_MANAGER_CLIENT))
#define KEYBOARD_IS_OBJECT_MANAGER_CLIENT_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), KEYBOARD_TYPE_OBJECT_MANAGER_CLIENT))

typedef struct _keyboardObjectManagerClient keyboardObjectManagerClient;
typedef struct _keyboardObjectManagerClientClass keyboardObjectManagerClientClass;
typedef struct _keyboardObjectManagerClientPrivate keyboardObjectManagerClientPrivate;

struct _keyboardObjectManagerClient
{
  /*< private >*/
  GDBusObjectManagerClient parent_instance;
  keyboardObjectManagerClientPrivate *priv;
};

struct _keyboardObjectManagerClientClass
{
  GDBusObjectManagerClientClass parent_class;
};

GType keyboard_object_manager_client_get_type (void) G_GNUC_CONST;

GType keyboard_object_manager_client_get_proxy_type (GDBusObjectManagerClient *manager, const gchar *object_path, const gchar *interface_name, gpointer user_data);

void keyboard_object_manager_client_new (
    GDBusConnection        *connection,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GAsyncReadyCallback     callback,
    gpointer                user_data);
GDBusObjectManager *keyboard_object_manager_client_new_finish (
    GAsyncResult        *res,
    GError             **error);
GDBusObjectManager *keyboard_object_manager_client_new_sync (
    GDBusConnection        *connection,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GError                **error);

void keyboard_object_manager_client_new_for_bus (
    GBusType                bus_type,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GAsyncReadyCallback     callback,
    gpointer                user_data);
GDBusObjectManager *keyboard_object_manager_client_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
GDBusObjectManager *keyboard_object_manager_client_new_for_bus_sync (
    GBusType                bus_type,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GError                **error);


G_END_DECLS

#endif /* __NET_KHPYLON_YOGA900_GENERATED_CODE_H__ */
