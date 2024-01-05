#ifndef _GST_MYELEMENT_H_
#define _GST_MYELEMENT_H_

#include <gst/base/gstbasesrc.h>
#include <stdio.h>

G_BEGIN_DECLS

#define GST_TYPE_MYELEMENT   (gst_myelement_get_type())
#define GST_MYELEMENT(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_MYELEMENT,GstMyelement))
#define GST_MYELEMENT_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_MYELEMENT,GstMyelementClass))
#define GST_IS_MYELEMENT(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_MYELEMENT))
#define GST_IS_MYELEMENT_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_MYELEMENT))

typedef struct _GstMyelement GstMyelement;
typedef struct _GstMyelementClass GstMyelementClass;



struct _GstMyelement
{
  GstBaseSrc base_myelement;
  gchar* location;
  FILE *fd;
};

struct _GstMyelementClass
{
  GstBaseSrcClass base_myelement_class;
};

GType gst_myelement_get_type (void);

G_END_DECLS

#endif
