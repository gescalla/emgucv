using System;
using System.Collections.Generic;
using System.Text;
using Emgu.Util;
using Emgu.CV.Structure;
using System.Runtime.InteropServices;

namespace Emgu.CV
{
   /// <summary>
   /// Oct-Tree
   /// </summary>
   public class OctTree : UnmanagedObject
   {
      #region PInvoke
      [DllImport(CvInvoke.EXTERN_LIBRARY)]
      private extern static IntPtr cvOctTreeCreate();

      [DllImport(CvInvoke.EXTERN_LIBRARY)]
      private extern static void cvOctTreeRelease(IntPtr tree);

      [DllImport(CvInvoke.EXTERN_LIBRARY)]
      private extern static void cvOctTreeBuildTree(IntPtr tree, IntPtr points, int numberOfPoints, int maxLevels, int minPoints);

      [DllImport(CvInvoke.EXTERN_LIBRARY)]
      private extern static void cvOctTreeGetPointsWithinSphere(IntPtr tree, MCvPoint3D32f center, float radius, IntPtr pointSeq);
      #endregion

      private MemStorage _storage;
      private Seq<MCvPoint3D32f> _pointSeq;

      /// <summary>
      /// Create an empty Oct-Tree
      /// </summary>
      public OctTree()
      {
         _ptr = cvOctTreeCreate();
         _storage = new MemStorage();
         _pointSeq = new Seq<MCvPoint3D32f>(_storage);
      }

      /// <summary>
      /// Create an Oct-Tree from the given points
      /// </summary>
      /// <param name="points">The points to be inserted into the Oct-Tree</param>
      /// <param name="maxLevels">The maximum levels of the Oct-Tree</param>
      /// <param name="minPoints">The minimum number of points in each level</param>
      public OctTree(MCvPoint3D32f[] points, int maxLevels, int minPoints)
         :this()
      {
         BuildTree(points, maxLevels, minPoints);
      }

      /// <summary>
      /// Build an Oct-Tree from the given points
      /// </summary>
      /// <param name="points">The points to be inserted into the Oct-Tree</param>
      /// <param name="maxLevels">The maximum levels of the Oct-Tree</param>
      /// <param name="minPoints">The minimum number of points in each level</param>
      public void BuildTree(MCvPoint3D32f[] points, int maxLevels, int minPoints)
      {
         GCHandle handle = GCHandle.Alloc(points, GCHandleType.Pinned);
         cvOctTreeBuildTree(_ptr, handle.AddrOfPinnedObject(), points.Length, maxLevels, minPoints);
         handle.Free();
      }

      /// <summary>
      /// Get the points within the specific sphere
      /// </summary>
      /// <param name="center">The center of the sphere</param>
      /// <param name="radius">The radius of the sphere</param>
      /// <returns>The points withing the specific sphere</returns>
      public MCvPoint3D32f[] GetPointsWithinSphere(MCvPoint3D32f center, float radius)
      {
         cvOctTreeGetPointsWithinSphere(_ptr, center, radius, _pointSeq);
         return _pointSeq.ToArray();
      }

      /// <summary>
      /// Release the managed memory associated with this Oct Tree
      /// </summary>
      protected override void ReleaseManagedResources()
      {
         _storage.Dispose();
         base.ReleaseManagedResources();
      }

      /// <summary>
      /// Release the Oct Tree
      /// </summary>
      protected override void DisposeObject()
      {
         cvOctTreeRelease(_ptr);
      }
   }
}
