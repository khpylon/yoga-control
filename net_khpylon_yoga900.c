/*
 * Generated by gdbus-codegen 2.46.2. DO NOT EDIT.
 *
 * The license of this code is the same as for the source it was derived from.
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "net_khpylon_yoga900.h"

#include <string.h>
#ifdef G_OS_UNIX
#  include <gio/gunixfdlist.h>
#endif

typedef struct
{
  GDBusArgInfo parent_struct;
  gboolean use_gvariant;
} _ExtendedGDBusArgInfo;

typedef struct
{
  GDBusMethodInfo parent_struct;
  const gchar *signal_name;
  gboolean pass_fdlist;
} _ExtendedGDBusMethodInfo;

typedef struct
{
  GDBusSignalInfo parent_struct;
  const gchar *signal_name;
} _ExtendedGDBusSignalInfo;

typedef struct
{
  GDBusPropertyInfo parent_struct;
  const gchar *hyphen_name;
  gboolean use_gvariant;
} _ExtendedGDBusPropertyInfo;

typedef struct
{
  GDBusInterfaceInfo parent_struct;
  const gchar *hyphen_name;
} _ExtendedGDBusInterfaceInfo;

typedef struct
{
  const _ExtendedGDBusPropertyInfo *info;
  guint prop_id;
  GValue orig_value; /* the value before the change */
} ChangedProperty;

static void
_changed_property_free (ChangedProperty *data)
{
  g_value_unset (&data->orig_value);
  g_free (data);
}

static gboolean
_g_strv_equal0 (gchar **a, gchar **b)
{
  gboolean ret = FALSE;
  guint n;
  if (a == NULL && b == NULL)
    {
      ret = TRUE;
      goto out;
    }
  if (a == NULL || b == NULL)
    goto out;
  if (g_strv_length (a) != g_strv_length (b))
    goto out;
  for (n = 0; a[n] != NULL; n++)
    if (g_strcmp0 (a[n], b[n]) != 0)
      goto out;
  ret = TRUE;
out:
  return ret;
}

static gboolean
_g_variant_equal0 (GVariant *a, GVariant *b)
{
  gboolean ret = FALSE;
  if (a == NULL && b == NULL)
    {
      ret = TRUE;
      goto out;
    }
  if (a == NULL || b == NULL)
    goto out;
  ret = g_variant_equal (a, b);
out:
  return ret;
}

G_GNUC_UNUSED static gboolean
_g_value_equal (const GValue *a, const GValue *b)
{
  gboolean ret = FALSE;
  g_assert (G_VALUE_TYPE (a) == G_VALUE_TYPE (b));
  switch (G_VALUE_TYPE (a))
    {
      case G_TYPE_BOOLEAN:
        ret = (g_value_get_boolean (a) == g_value_get_boolean (b));
        break;
      case G_TYPE_UCHAR:
        ret = (g_value_get_uchar (a) == g_value_get_uchar (b));
        break;
      case G_TYPE_INT:
        ret = (g_value_get_int (a) == g_value_get_int (b));
        break;
      case G_TYPE_UINT:
        ret = (g_value_get_uint (a) == g_value_get_uint (b));
        break;
      case G_TYPE_INT64:
        ret = (g_value_get_int64 (a) == g_value_get_int64 (b));
        break;
      case G_TYPE_UINT64:
        ret = (g_value_get_uint64 (a) == g_value_get_uint64 (b));
        break;
      case G_TYPE_DOUBLE:
        {
          /* Avoid -Wfloat-equal warnings by doing a direct bit compare */
          gdouble da = g_value_get_double (a);
          gdouble db = g_value_get_double (b);
          ret = memcmp (&da, &db, sizeof (gdouble)) == 0;
        }
        break;
      case G_TYPE_STRING:
        ret = (g_strcmp0 (g_value_get_string (a), g_value_get_string (b)) == 0);
        break;
      case G_TYPE_VARIANT:
        ret = _g_variant_equal0 (g_value_get_variant (a), g_value_get_variant (b));
        break;
      default:
        if (G_VALUE_TYPE (a) == G_TYPE_STRV)
          ret = _g_strv_equal0 (g_value_get_boxed (a), g_value_get_boxed (b));
        else
          g_critical ("_g_value_equal() does not handle type %s", g_type_name (G_VALUE_TYPE (a)));
        break;
    }
  return ret;
}

/* ------------------------------------------------------------------------
 * Code for interface net.khpylon.yoga900keyboard
 * ------------------------------------------------------------------------
 */

/**
 * SECTION:keyboard
 * @title: keyboard
 * @short_description: Generated C code for the net.khpylon.yoga900keyboard D-Bus interface
 *
 * This section contains code for working with the <link linkend="gdbus-interface-net-khpylon-yoga900keyboard.top_of_page">net.khpylon.yoga900keyboard</link> D-Bus interface in C.
 */

/* ---- Introspection data for net.khpylon.yoga900keyboard ---- */

static const _ExtendedGDBusPropertyInfo _keyboard__property_info_laptop_mode =
{
  {
    -1,
    (gchar *) "LaptopMode",
    (gchar *) "b",
    G_DBUS_PROPERTY_INFO_FLAGS_READABLE,
    NULL
  },
  "laptop-mode",
  FALSE
};

static const _ExtendedGDBusPropertyInfo * const _keyboard__property_info_pointers[] =
{
  &_keyboard__property_info_laptop_mode,
  NULL
};

static const _ExtendedGDBusInterfaceInfo _keyboard__interface_info =
{
  {
    -1,
    (gchar *) "net.khpylon.yoga900keyboard",
    NULL,
    NULL,
    (GDBusPropertyInfo **) &_keyboard__property_info_pointers,
    NULL
  },
  "",
};


/**
 * keyboard__interface_info:
 *
 * Gets a machine-readable description of the <link linkend="gdbus-interface-net-khpylon-yoga900keyboard.top_of_page">net.khpylon.yoga900keyboard</link> D-Bus interface.
 *
 * Returns: (transfer none): A #GDBusInterfaceInfo. Do not free.
 */
GDBusInterfaceInfo *
keyboard__interface_info (void)
{
  return (GDBusInterfaceInfo *) &_keyboard__interface_info.parent_struct;
}

/**
 * keyboard__override_properties:
 * @klass: The class structure for a #GObject<!-- -->-derived class.
 * @property_id_begin: The property id to assign to the first overridden property.
 *
 * Overrides all #GObject properties in the #keyboard interface for a concrete class.
 * The properties are overridden in the order they are defined.
 *
 * Returns: The last property id.
 */
guint
keyboard__override_properties (GObjectClass *klass, guint property_id_begin)
{
  g_object_class_override_property (klass, property_id_begin++, "laptop-mode");
  return property_id_begin - 1;
}



/**
 * keyboard:
 *
 * Abstract interface type for the D-Bus interface <link linkend="gdbus-interface-net-khpylon-yoga900keyboard.top_of_page">net.khpylon.yoga900keyboard</link>.
 */

/**
 * keyboardIface:
 * @parent_iface: The parent interface.
 * @get_laptop_mode: Getter for the #keyboard:laptop-mode property.
 *
 * Virtual table for the D-Bus interface <link linkend="gdbus-interface-net-khpylon-yoga900keyboard.top_of_page">net.khpylon.yoga900keyboard</link>.
 */

typedef keyboardIface keyboardInterface;
G_DEFINE_INTERFACE (keyboard, keyboard_, G_TYPE_OBJECT);

static void
keyboard__default_init (keyboardIface *iface)
{
  /* GObject properties for D-Bus properties: */
  /**
   * keyboard:laptop-mode:
   *
   * Represents the D-Bus property <link linkend="gdbus-property-net-khpylon-yoga900keyboard.LaptopMode">"LaptopMode"</link>.
   *
   * Since the D-Bus property for this #GObject property is readable but not writable, it is meaningful to read from it on both the client- and service-side. It is only meaningful, however, to write to it on the service-side.
   */
  g_object_interface_install_property (iface,
    g_param_spec_boolean ("laptop-mode", "LaptopMode", "LaptopMode", FALSE, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));
}

/**
 * keyboard__get_laptop_mode: (skip)
 * @object: A #keyboard.
 *
 * Gets the value of the <link linkend="gdbus-property-net-khpylon-yoga900keyboard.LaptopMode">"LaptopMode"</link> D-Bus property.
 *
 * Since this D-Bus property is readable, it is meaningful to use this function on both the client- and service-side.
 *
 * Returns: The property value.
 */
gboolean 
keyboard__get_laptop_mode (keyboard *object)
{
  return KEYBOARD__GET_IFACE (object)->get_laptop_mode (object);
}

/**
 * keyboard__set_laptop_mode: (skip)
 * @object: A #keyboard.
 * @value: The value to set.
 *
 * Sets the <link linkend="gdbus-property-net-khpylon-yoga900keyboard.LaptopMode">"LaptopMode"</link> D-Bus property to @value.
 *
 * Since this D-Bus property is not writable, it is only meaningful to use this function on the service-side.
 */
void
keyboard__set_laptop_mode (keyboard *object, gboolean value)
{
  g_object_set (G_OBJECT (object), "laptop-mode", value, NULL);
}


/* ------------------------------------------------------------------------ */

/**
 * keyboardSkeleton:
 *
 * The #keyboardSkeleton structure contains only private data and should only be accessed using the provided API.
 */

/**
 * keyboardSkeletonClass:
 * @parent_class: The parent class.
 *
 * Class structure for #keyboardSkeleton.
 */

struct _keyboardSkeletonPrivate
{
  GValue *properties;
  GList *changed_properties;
  GSource *changed_properties_idle_source;
  GMainContext *context;
  GMutex lock;
};

static void
_keyboard__skeleton_handle_method_call (
  GDBusConnection *connection G_GNUC_UNUSED,
  const gchar *sender G_GNUC_UNUSED,
  const gchar *object_path G_GNUC_UNUSED,
  const gchar *interface_name,
  const gchar *method_name,
  GVariant *parameters,
  GDBusMethodInvocation *invocation,
  gpointer user_data)
{
  keyboardSkeleton *skeleton = KEYBOARD__SKELETON (user_data);
  _ExtendedGDBusMethodInfo *info;
  GVariantIter iter;
  GVariant *child;
  GValue *paramv;
  guint num_params;
  guint num_extra;
  guint n;
  guint signal_id;
  GValue return_value = G_VALUE_INIT;
  info = (_ExtendedGDBusMethodInfo *) g_dbus_method_invocation_get_method_info (invocation);
  g_assert (info != NULL);
  num_params = g_variant_n_children (parameters);
  num_extra = info->pass_fdlist ? 3 : 2;  paramv = g_new0 (GValue, num_params + num_extra);
  n = 0;
  g_value_init (&paramv[n], KEYBOARD_TYPE_);
  g_value_set_object (&paramv[n++], skeleton);
  g_value_init (&paramv[n], G_TYPE_DBUS_METHOD_INVOCATION);
  g_value_set_object (&paramv[n++], invocation);
  if (info->pass_fdlist)
    {
#ifdef G_OS_UNIX
      g_value_init (&paramv[n], G_TYPE_UNIX_FD_LIST);
      g_value_set_object (&paramv[n++], g_dbus_message_get_unix_fd_list (g_dbus_method_invocation_get_message (invocation)));
#else
      g_assert_not_reached ();
#endif
    }
  g_variant_iter_init (&iter, parameters);
  while ((child = g_variant_iter_next_value (&iter)) != NULL)
    {
      _ExtendedGDBusArgInfo *arg_info = (_ExtendedGDBusArgInfo *) info->parent_struct.in_args[n - num_extra];
      if (arg_info->use_gvariant)
        {
          g_value_init (&paramv[n], G_TYPE_VARIANT);
          g_value_set_variant (&paramv[n], child);
          n++;
        }
      else
        g_dbus_gvariant_to_gvalue (child, &paramv[n++]);
      g_variant_unref (child);
    }
  signal_id = g_signal_lookup (info->signal_name, KEYBOARD_TYPE_);
  g_value_init (&return_value, G_TYPE_BOOLEAN);
  g_signal_emitv (paramv, signal_id, 0, &return_value);
  if (!g_value_get_boolean (&return_value))
    g_dbus_method_invocation_return_error (invocation, G_DBUS_ERROR, G_DBUS_ERROR_UNKNOWN_METHOD, "Method %s is not implemented on interface %s", method_name, interface_name);
  g_value_unset (&return_value);
  for (n = 0; n < num_params + num_extra; n++)
    g_value_unset (&paramv[n]);
  g_free (paramv);
}

static GVariant *
_keyboard__skeleton_handle_get_property (
  GDBusConnection *connection G_GNUC_UNUSED,
  const gchar *sender G_GNUC_UNUSED,
  const gchar *object_path G_GNUC_UNUSED,
  const gchar *interface_name G_GNUC_UNUSED,
  const gchar *property_name,
  GError **error,
  gpointer user_data)
{
  keyboardSkeleton *skeleton = KEYBOARD__SKELETON (user_data);
  GValue value = G_VALUE_INIT;
  GParamSpec *pspec;
  _ExtendedGDBusPropertyInfo *info;
  GVariant *ret;
  ret = NULL;
  info = (_ExtendedGDBusPropertyInfo *) g_dbus_interface_info_lookup_property ((GDBusInterfaceInfo *) &_keyboard__interface_info.parent_struct, property_name);
  g_assert (info != NULL);
  pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (skeleton), info->hyphen_name);
  if (pspec == NULL)
    {
      g_set_error (error, G_DBUS_ERROR, G_DBUS_ERROR_INVALID_ARGS, "No property with name %s", property_name);
    }
  else
    {
      g_value_init (&value, pspec->value_type);
      g_object_get_property (G_OBJECT (skeleton), info->hyphen_name, &value);
      ret = g_dbus_gvalue_to_gvariant (&value, G_VARIANT_TYPE (info->parent_struct.signature));
      g_value_unset (&value);
    }
  return ret;
}

static gboolean
_keyboard__skeleton_handle_set_property (
  GDBusConnection *connection G_GNUC_UNUSED,
  const gchar *sender G_GNUC_UNUSED,
  const gchar *object_path G_GNUC_UNUSED,
  const gchar *interface_name G_GNUC_UNUSED,
  const gchar *property_name,
  GVariant *variant,
  GError **error,
  gpointer user_data)
{
  keyboardSkeleton *skeleton = KEYBOARD__SKELETON (user_data);
  GValue value = G_VALUE_INIT;
  GParamSpec *pspec;
  _ExtendedGDBusPropertyInfo *info;
  gboolean ret;
  ret = FALSE;
  info = (_ExtendedGDBusPropertyInfo *) g_dbus_interface_info_lookup_property ((GDBusInterfaceInfo *) &_keyboard__interface_info.parent_struct, property_name);
  g_assert (info != NULL);
  pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (skeleton), info->hyphen_name);
  if (pspec == NULL)
    {
      g_set_error (error, G_DBUS_ERROR, G_DBUS_ERROR_INVALID_ARGS, "No property with name %s", property_name);
    }
  else
    {
      if (info->use_gvariant)
        g_value_set_variant (&value, variant);
      else
        g_dbus_gvariant_to_gvalue (variant, &value);
      g_object_set_property (G_OBJECT (skeleton), info->hyphen_name, &value);
      g_value_unset (&value);
      ret = TRUE;
    }
  return ret;
}

static const GDBusInterfaceVTable _keyboard__skeleton_vtable =
{
  _keyboard__skeleton_handle_method_call,
  _keyboard__skeleton_handle_get_property,
  _keyboard__skeleton_handle_set_property,
  {NULL}
};

static GDBusInterfaceInfo *
keyboard__skeleton_dbus_interface_get_info (GDBusInterfaceSkeleton *skeleton G_GNUC_UNUSED)
{
  return keyboard__interface_info ();
}

GDBusInterfaceVTable *
keyboard__skeleton_dbus_interface_get_vtable (GDBusInterfaceSkeleton *skeleton G_GNUC_UNUSED)
{
  return (GDBusInterfaceVTable *) &_keyboard__skeleton_vtable;
}

static GVariant *
keyboard__skeleton_dbus_interface_get_properties (GDBusInterfaceSkeleton *_skeleton)
{
  keyboardSkeleton *skeleton = KEYBOARD__SKELETON (_skeleton);

  GVariantBuilder builder;
  guint n;
  g_variant_builder_init (&builder, G_VARIANT_TYPE ("a{sv}"));
  if (_keyboard__interface_info.parent_struct.properties == NULL)
    goto out;
  for (n = 0; _keyboard__interface_info.parent_struct.properties[n] != NULL; n++)
    {
      GDBusPropertyInfo *info = _keyboard__interface_info.parent_struct.properties[n];
      if (info->flags & G_DBUS_PROPERTY_INFO_FLAGS_READABLE)
        {
          GVariant *value;
          value = _keyboard__skeleton_handle_get_property (g_dbus_interface_skeleton_get_connection (G_DBUS_INTERFACE_SKELETON (skeleton)), NULL, g_dbus_interface_skeleton_get_object_path (G_DBUS_INTERFACE_SKELETON (skeleton)), "net.khpylon.yoga900keyboard", info->name, NULL, skeleton);
          if (value != NULL)
            {
              g_variant_take_ref (value);
              g_variant_builder_add (&builder, "{sv}", info->name, value);
              g_variant_unref (value);
            }
        }
    }
out:
  return g_variant_builder_end (&builder);
}

static gboolean _keyboard__emit_changed (gpointer user_data);

static void
keyboard__skeleton_dbus_interface_flush (GDBusInterfaceSkeleton *_skeleton)
{
  keyboardSkeleton *skeleton = KEYBOARD__SKELETON (_skeleton);
  gboolean emit_changed = FALSE;

  g_mutex_lock (&skeleton->priv->lock);
  if (skeleton->priv->changed_properties_idle_source != NULL)
    {
      g_source_destroy (skeleton->priv->changed_properties_idle_source);
      skeleton->priv->changed_properties_idle_source = NULL;
      emit_changed = TRUE;
    }
  g_mutex_unlock (&skeleton->priv->lock);

  if (emit_changed)
    _keyboard__emit_changed (skeleton);
}

static void keyboard__skeleton_iface_init (keyboardIface *iface);
#if GLIB_VERSION_MAX_ALLOWED >= GLIB_VERSION_2_38
G_DEFINE_TYPE_WITH_CODE (keyboardSkeleton, keyboard__skeleton, G_TYPE_DBUS_INTERFACE_SKELETON,
                         G_ADD_PRIVATE (keyboardSkeleton)
                         G_IMPLEMENT_INTERFACE (KEYBOARD_TYPE_, keyboard__skeleton_iface_init));

#else
G_DEFINE_TYPE_WITH_CODE (keyboardSkeleton, keyboard__skeleton, G_TYPE_DBUS_INTERFACE_SKELETON,
                         G_IMPLEMENT_INTERFACE (KEYBOARD_TYPE_, keyboard__skeleton_iface_init));

#endif
static void
keyboard__skeleton_finalize (GObject *object)
{
  keyboardSkeleton *skeleton = KEYBOARD__SKELETON (object);
  guint n;
  for (n = 0; n < 1; n++)
    g_value_unset (&skeleton->priv->properties[n]);
  g_free (skeleton->priv->properties);
  g_list_free_full (skeleton->priv->changed_properties, (GDestroyNotify) _changed_property_free);
  if (skeleton->priv->changed_properties_idle_source != NULL)
    g_source_destroy (skeleton->priv->changed_properties_idle_source);
  g_main_context_unref (skeleton->priv->context);
  g_mutex_clear (&skeleton->priv->lock);
  G_OBJECT_CLASS (keyboard__skeleton_parent_class)->finalize (object);
}

static void
keyboard__skeleton_get_property (GObject      *object,
  guint         prop_id,
  GValue       *value,
  GParamSpec   *pspec G_GNUC_UNUSED)
{
  keyboardSkeleton *skeleton = KEYBOARD__SKELETON (object);
  g_assert (prop_id != 0 && prop_id - 1 < 1);
  g_mutex_lock (&skeleton->priv->lock);
  g_value_copy (&skeleton->priv->properties[prop_id - 1], value);
  g_mutex_unlock (&skeleton->priv->lock);
}

static gboolean
_keyboard__emit_changed (gpointer user_data)
{
  keyboardSkeleton *skeleton = KEYBOARD__SKELETON (user_data);
  GList *l;
  GVariantBuilder builder;
  GVariantBuilder invalidated_builder;
  guint num_changes;

  g_mutex_lock (&skeleton->priv->lock);
  g_variant_builder_init (&builder, G_VARIANT_TYPE ("a{sv}"));
  g_variant_builder_init (&invalidated_builder, G_VARIANT_TYPE ("as"));
  for (l = skeleton->priv->changed_properties, num_changes = 0; l != NULL; l = l->next)
    {
      ChangedProperty *cp = l->data;
      GVariant *variant;
      const GValue *cur_value;

      cur_value = &skeleton->priv->properties[cp->prop_id - 1];
      if (!_g_value_equal (cur_value, &cp->orig_value))
        {
          variant = g_dbus_gvalue_to_gvariant (cur_value, G_VARIANT_TYPE (cp->info->parent_struct.signature));
          g_variant_builder_add (&builder, "{sv}", cp->info->parent_struct.name, variant);
          g_variant_unref (variant);
          num_changes++;
        }
    }
  if (num_changes > 0)
    {
      GList *connections, *ll;
      GVariant *signal_variant;
      signal_variant = g_variant_ref_sink (g_variant_new ("(sa{sv}as)", "net.khpylon.yoga900keyboard",
                                           &builder, &invalidated_builder));
      connections = g_dbus_interface_skeleton_get_connections (G_DBUS_INTERFACE_SKELETON (skeleton));
      for (ll = connections; ll != NULL; ll = ll->next)
        {
          GDBusConnection *connection = ll->data;

          g_dbus_connection_emit_signal (connection,
                                         NULL, g_dbus_interface_skeleton_get_object_path (G_DBUS_INTERFACE_SKELETON (skeleton)),
                                         "org.freedesktop.DBus.Properties",
                                         "PropertiesChanged",
                                         signal_variant,
                                         NULL);
        }
      g_variant_unref (signal_variant);
      g_list_free_full (connections, g_object_unref);
    }
  else
    {
      g_variant_builder_clear (&builder);
      g_variant_builder_clear (&invalidated_builder);
    }
  g_list_free_full (skeleton->priv->changed_properties, (GDestroyNotify) _changed_property_free);
  skeleton->priv->changed_properties = NULL;
  skeleton->priv->changed_properties_idle_source = NULL;
  g_mutex_unlock (&skeleton->priv->lock);
  return FALSE;
}

static void
_keyboard__schedule_emit_changed (keyboardSkeleton *skeleton, const _ExtendedGDBusPropertyInfo *info, guint prop_id, const GValue *orig_value)
{
  ChangedProperty *cp;
  GList *l;
  cp = NULL;
  for (l = skeleton->priv->changed_properties; l != NULL; l = l->next)
    {
      ChangedProperty *i_cp = l->data;
      if (i_cp->info == info)
        {
          cp = i_cp;
          break;
        }
    }
  if (cp == NULL)
    {
      cp = g_new0 (ChangedProperty, 1);
      cp->prop_id = prop_id;
      cp->info = info;
      skeleton->priv->changed_properties = g_list_prepend (skeleton->priv->changed_properties, cp);
      g_value_init (&cp->orig_value, G_VALUE_TYPE (orig_value));
      g_value_copy (orig_value, &cp->orig_value);
    }
}

static void
keyboard__skeleton_notify (GObject      *object,
  GParamSpec *pspec G_GNUC_UNUSED)
{
  keyboardSkeleton *skeleton = KEYBOARD__SKELETON (object);
  g_mutex_lock (&skeleton->priv->lock);
  if (skeleton->priv->changed_properties != NULL &&
      skeleton->priv->changed_properties_idle_source == NULL)
    {
      skeleton->priv->changed_properties_idle_source = g_idle_source_new ();
      g_source_set_priority (skeleton->priv->changed_properties_idle_source, G_PRIORITY_DEFAULT);
      g_source_set_callback (skeleton->priv->changed_properties_idle_source, _keyboard__emit_changed, g_object_ref (skeleton), (GDestroyNotify) g_object_unref);
      g_source_set_name (skeleton->priv->changed_properties_idle_source, "[generated] _keyboard__emit_changed");
      g_source_attach (skeleton->priv->changed_properties_idle_source, skeleton->priv->context);
      g_source_unref (skeleton->priv->changed_properties_idle_source);
    }
  g_mutex_unlock (&skeleton->priv->lock);
}

static void
keyboard__skeleton_set_property (GObject      *object,
  guint         prop_id,
  const GValue *value,
  GParamSpec   *pspec)
{
  keyboardSkeleton *skeleton = KEYBOARD__SKELETON (object);
  g_assert (prop_id != 0 && prop_id - 1 < 1);
  g_mutex_lock (&skeleton->priv->lock);
  g_object_freeze_notify (object);
  if (!_g_value_equal (value, &skeleton->priv->properties[prop_id - 1]))
    {
      if (g_dbus_interface_skeleton_get_connection (G_DBUS_INTERFACE_SKELETON (skeleton)) != NULL)
        _keyboard__schedule_emit_changed (skeleton, _keyboard__property_info_pointers[prop_id - 1], prop_id, &skeleton->priv->properties[prop_id - 1]);
      g_value_copy (value, &skeleton->priv->properties[prop_id - 1]);
      g_object_notify_by_pspec (object, pspec);
    }
  g_mutex_unlock (&skeleton->priv->lock);
  g_object_thaw_notify (object);
}

static void
keyboard__skeleton_init (keyboardSkeleton *skeleton)
{
#if GLIB_VERSION_MAX_ALLOWED >= GLIB_VERSION_2_38
  skeleton->priv = keyboard__skeleton_get_instance_private (skeleton);
#else
  skeleton->priv = G_TYPE_INSTANCE_GET_PRIVATE (skeleton, KEYBOARD_TYPE__SKELETON, keyboardSkeletonPrivate);
#endif

  g_mutex_init (&skeleton->priv->lock);
  skeleton->priv->context = g_main_context_ref_thread_default ();
  skeleton->priv->properties = g_new0 (GValue, 1);
  g_value_init (&skeleton->priv->properties[0], G_TYPE_BOOLEAN);
}

static gboolean 
keyboard__skeleton_get_laptop_mode (keyboard *object)
{
  keyboardSkeleton *skeleton = KEYBOARD__SKELETON (object);
  gboolean value;
  g_mutex_lock (&skeleton->priv->lock);
  value = g_value_get_boolean (&(skeleton->priv->properties[0]));
  g_mutex_unlock (&skeleton->priv->lock);
  return value;
}

static void
keyboard__skeleton_class_init (keyboardSkeletonClass *klass)
{
  GObjectClass *gobject_class;
  GDBusInterfaceSkeletonClass *skeleton_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = keyboard__skeleton_finalize;
  gobject_class->get_property = keyboard__skeleton_get_property;
  gobject_class->set_property = keyboard__skeleton_set_property;
  gobject_class->notify       = keyboard__skeleton_notify;


  keyboard__override_properties (gobject_class, 1);

  skeleton_class = G_DBUS_INTERFACE_SKELETON_CLASS (klass);
  skeleton_class->get_info = keyboard__skeleton_dbus_interface_get_info;
  skeleton_class->get_properties = keyboard__skeleton_dbus_interface_get_properties;
  skeleton_class->flush = keyboard__skeleton_dbus_interface_flush;
  skeleton_class->get_vtable = keyboard__skeleton_dbus_interface_get_vtable;

#if GLIB_VERSION_MAX_ALLOWED < GLIB_VERSION_2_38
  g_type_class_add_private (klass, sizeof (keyboardSkeletonPrivate));
#endif
}

static void
keyboard__skeleton_iface_init (keyboardIface *iface)
{
  iface->get_laptop_mode = keyboard__skeleton_get_laptop_mode;
}

/**
 * keyboard__skeleton_new:
 *
 * Creates a skeleton object for the D-Bus interface <link linkend="gdbus-interface-net-khpylon-yoga900keyboard.top_of_page">net.khpylon.yoga900keyboard</link>.
 *
 * Returns: (transfer full) (type keyboardSkeleton): The skeleton object.
 */
keyboard *
keyboard__skeleton_new (void)
{
  return KEYBOARD_ (g_object_new (KEYBOARD_TYPE__SKELETON, NULL));
}

